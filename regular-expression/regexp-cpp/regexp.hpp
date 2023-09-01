// 实现一个简单的正则表达式引擎 (C++ 版本)
//
// 支持的操作符:
//     连接 ab
//     克林闭包 a*
//     取并 a|b
//     一个或多个 a+
//     一个或0个 a?
//     范围 比如 [a-Z], [0-9]
// 核心步骤:
//     NfaParser().Parse()      解析正则表达式，构造 NFA
//     DfaBuilder().Build()     NFA 转换为 DFA
//     DfaMinifier().Minify()   压缩 DFA 状态数
//
// 编译选项: -std=c++11 以上
// 博客 - 实现一个简单的正则表达式引擎
// https://writings.sh/post/regexp

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifndef REGEXP_H
#define REGEXP_H

namespace regexp {
// Util: std::stack 的 pop 不方便，这里封一个简单的 wrapper
template <typename T>
class stack {
   public:
    void push(T e) { s.push(e); };
    T pop() {
        auto e = s.top();
        s.pop();
        return e;
    };
    T top() const { return s.top(); }
    bool empty() const { return s.empty(); }

   private:
    std::stack<T> s;
};

// Copy elements in set a but not in set b to set c.
template <typename T, typename Cmp = std::less<T>>
void set_sub(const std::set<T, Cmp>& a, const std::set<T, Cmp>& b,
             std::set<T, Cmp>& c) {
    for (auto& x : a)
        if (b.find(x) == b.end()) c.insert(x);
}

// 符号
typedef char C;

// 空符号
static const C EPSILON = '\0';

// 操作符
enum Op : C {
    OP_CONCAT = '&',
    OP_UNION = '|',
    OP_CLOSURE = '*',
    OP_LEFT_PAIR = '(',
    OP_RIGHT_PAIR = ')',
    OP_PLUS = '+',
    OP_OPTIONAL = '?',
    OP_RANGE_START = '[',
    OP_RANGE_END = ']',
    OP_RANGE_TO = '-',
};

// 是否是运算符
static bool IsCalculationOperator(C c) {
    switch (c) {
        case OP_CONCAT:
            return true;
        case OP_UNION:
            return true;
        case OP_CLOSURE:
            return true;
        case OP_PLUS:
            return true;
        case OP_OPTIONAL:
            return true;
        default:
            return false;
    }
}

// 运算符优先级
static int GetOperatorPriority(Op op) {
    switch (op) {
        case OP_CONCAT:
            return 1;
        case OP_UNION:
            return 1;
        case OP_CLOSURE:
            return 2;
        case OP_PLUS:
            return 2;
        case OP_OPTIONAL:
            return 2;
        default:
            return 0;
    };
}

// 是否一个存在对右侧字符有作用的操作符 (重载)
static bool IsRightActingOperator(C c) {
    switch (c) {
        case OP_CONCAT:
            [[fallthrough]];
        case OP_UNION:
            [[fallthrough]];
        case OP_LEFT_PAIR:
            return true;
        default:
            return false;
    }
}

// 是否可以在 x 左侧插入 连接符?
static bool IsAbleInsertConcat(C c) {
    switch (c) {
        case OP_CONCAT:
            [[fallthrough]];
        case OP_UNION:
            [[fallthrough]];
        case OP_CLOSURE:
            [[fallthrough]];
        case OP_RIGHT_PAIR:
            [[fallthrough]];
        case OP_PLUS:
            [[fallthrough]];
        case OP_OPTIONAL:
            [[fallthrough]];
        case OP_RANGE_END:
            [[fallthrough]];
        case OP_RANGE_TO:
            return false;
        default:
            // 左括号, 一般字符可以
            return true;
    }
}

// 状态的基础类
class State {
   protected:
    int id;
    bool is_end;

   public:
    // 用于比较两个状态的 Comparator
    class PtrCmp {
       public:
        bool operator()(const std::shared_ptr<State>& a,
                        const std::shared_ptr<State>& b) const {
            return a->Id() < b->Id();
        };
    };

    State(int id, bool is_end) : id(id), is_end(is_end){};
    int Id() const { return id; };
    bool IsEnd() const { return is_end; };
};

class NfaState : public State {
   public:
    // Set of NfaState pointers.
    typedef std::set<std::shared_ptr<NfaState>, PtrCmp> Set;
    // Transition table: Char => Set of NfaStates.
    typedef std::unordered_map<C, Set> Table;

    // 构造函数
    NfaState(int id, bool is_end) : State(id, is_end){};

    // 返回只读的跳转表
    const Table& Transitions() const { return transitions; };

    // 添加从此状态出发的一条跳转, 出边字符是 c, 目标状态是 to
    void AddTransition(C c, const std::shared_ptr<NfaState>& to) {
        transitions[c].insert(to);
        // 不再能成为终态
        if (is_end) is_end = false;
    };

    // 返回此状态经过给定符号可跳转到的目标状态集合
    // 如果不接受此符号，抛错.
    const NfaState::Set& Nexts(C c) const { return transitions.at(c); }

    // 判断状态转换是否接受符号 c.
    bool AcceptC(C c) const { return transitions.find(c) != transitions.end(); }

   private:
    Table transitions;
};

class Nfa {
   public:
    std::shared_ptr<NfaState> start = nullptr;
    std::shared_ptr<NfaState> end = nullptr;
    Nfa(const std::shared_ptr<NfaState>& start,
        const std::shared_ptr<NfaState>& end)
        : start(start), end(end){};
};

// 从 Regexp 字符串构造 Nfa 自动机
class NfaParser {
    // 待运算的 Nfa 栈
    typedef stack<std::shared_ptr<Nfa>> NfaStack;
    // 待运算的运算符栈
    typedef stack<Op> OpStack;
    // 范围, start, end
    typedef std::pair<C, C> range;

   private:
    // 状态计数器
    int state_no = 0;

    // 新建一个 NfaState.
    std::shared_ptr<NfaState> NewState(bool is_end) {
        return std::make_shared<NfaState>(++state_no, is_end);
    };

    // 从符号创建一个 Nfa.
    //             ch
    //     start ------> end
    std::shared_ptr<Nfa> CreateNfaFromSymbol(C c) {
        auto start = NewState(false);
        auto end = NewState(true);
        start->AddTransition(c, end);
        return std::make_shared<Nfa>(start, end);
    }

    // 从多个符号创建一个 Nfa.
    std::shared_ptr<Nfa> CreateNfaFromSymbols(const std::set<C>& chs) {
        auto start = NewState(false);
        auto end = NewState(true);
        if (!chs.empty()) {
            for (auto& c : chs) {
                start->AddTransition(c, end);
            }
        } else {
            start->AddTransition(EPSILON, end);
        }
        return std::make_shared<Nfa>(start, end);
    }

    // 从范围列表创建 Nfa
    std::shared_ptr<Nfa> CreateNfaFromRanges(std::vector<range>& ranges) {
        std::set<C> chs;
        for (auto& range : ranges) {
            for (auto x = range.first; x <= range.second; x++) {
                chs.insert(x);
            }
        }
        return CreateNfaFromSymbols(chs);
    }

    // 连接两个 Nfa
    //    a: 1 -> 2
    //    b: 3 -> 4
    //               e
    //    ab: 1 -> 2 -> 3 -> 4
    std::shared_ptr<Nfa> NfaConcat(const std::shared_ptr<Nfa>& a,
                                   const std::shared_ptr<Nfa>& b) {
        a->end->AddTransition(EPSILON, b->start);  // 2->3
        return std::make_shared<Nfa>(a->start, b->end);
    };

    // 两个 Nfa 的或操作
    //    a: 1 -> 2
    //    b: 3 -> 4
    //    a|b:
    //           e         e
    //          +-> 1 -> 2 -+
    //       5->+           +-> 6
    //          +-> 3 -> 4 -+
    //           e         e
    std::shared_ptr<Nfa> NfaUnion(const std::shared_ptr<Nfa>& a,
                                  const std::shared_ptr<Nfa>& b) {
        auto start = NewState(false);             // 5
        auto end = NewState(true);                // 6
        start->AddTransition(EPSILON, a->start);  // 5->1
        start->AddTransition(EPSILON, b->start);  // 5->3
        a->end->AddTransition(EPSILON, end);      // 2->6
        b->end->AddTransition(EPSILON, end);      // 4->6
        return std::make_shared<Nfa>(start, end);
    };

    // 克林闭包
    //
    //    a: 1->2
    //    a*:
    //               e
    //             +----+
    //          e  V    | e
    //        3 -> 1 -> 2 -> 4
    //        |              ^
    //        +--------------+
    //                e
    std::shared_ptr<Nfa> NfaClosure(const std::shared_ptr<Nfa>& a) {
        auto start = NewState(false);              // 3
        auto end = NewState(true);                 // 4
        a->end->AddTransition(EPSILON, a->start);  // 2->1
        start->AddTransition(EPSILON, a->start);   // 3->1
        a->end->AddTransition(EPSILON, end);       // 2->4
        start->AddTransition(EPSILON, end);        // 3->4
        return std::make_shared<Nfa>(start, end);
    };

    // a+ 即 aa*
    std::shared_ptr<Nfa> NfaPlus(const std::shared_ptr<Nfa>& a) {
        return NfaConcat(a, NfaClosure(a));
    }

    // a? 可选
    //    a: 1->2
    //    a?:
    //          e         3
    //        3 -> 1 -> 2 -> 4
    //        |              ^
    //        +--------------+
    //                e
    std::shared_ptr<Nfa> NfaOptional(const std::shared_ptr<Nfa>& a) {
        auto start = NewState(false);             // 3
        auto end = NewState(true);                // 4
        start->AddTransition(EPSILON, a->start);  // 3->1
        a->end->AddTransition(EPSILON, end);      // 2->4
        start->AddTransition(EPSILON, end);       // 3->4
        return std::make_shared<Nfa>(start, end);
    }

    void Calc(NfaStack& nfa_stack, OpStack& op_stack) {
        if (op_stack.empty()) return;
        // 弹出一个运算符
        auto op = op_stack.pop();
        switch (op) {
            case OP_CLOSURE: {
                auto a = nfa_stack.pop();
                nfa_stack.push(NfaClosure(a));
            }; break;
            case OP_CONCAT: {
                auto b = nfa_stack.pop();
                auto a = nfa_stack.pop();
                nfa_stack.push(NfaConcat(a, b));
            }; break;
            case OP_UNION: {
                auto b = nfa_stack.pop();
                auto a = nfa_stack.pop();
                nfa_stack.push(NfaUnion(a, b));
            }; break;
            case OP_PLUS: {
                auto a = nfa_stack.pop();
                nfa_stack.push(NfaPlus(a));
            } break;
            case OP_OPTIONAL: {
                auto a = nfa_stack.pop();
                nfa_stack.push(NfaOptional(a));
            } break;
            default:
                break;
        }
    }

    // 规整输入字符串, 在相邻符号间插入 & 符号
    // e.g. 'ab|c' => 'a&b|c'
    //     'a*c' => 'a*&c'
    //     '(a)b' => '(a)&b'
    //     'a(ab)' => 'a&(a&b)'
    // 范围内不可插入连接符号.
    std::string Normalize(const std::string& s) {
        std::string s1;
        bool is_in_range = false;
        for (auto& c : s) {
            if (IsAbleInsertConcat(c) && !s1.empty() &&
                !IsRightActingOperator(s1.back()) && !is_in_range) {
                // 可以插入 & 符号,
                // 并且前一个符号有向右贴合的作用，那么可以插入连接符
                s1.push_back(OP_CONCAT);
            }
            if (c == OP_RANGE_START)
                is_in_range = true;
            else if (c == OP_RANGE_END)
                is_in_range = false;
            s1.push_back(c);
        }
        std::cout << "Normalized to :" << s1 << std::endl;
        return s1;
    }

   public:
    // 采用 Dijkstra 双栈法进行表达式求值
    std::shared_ptr<Nfa> Parse(const std::string& s) {
        NfaStack nfa_stack;
        OpStack op_stack;

        auto s1 = Normalize(s);

        // 避免空串
        nfa_stack.push(CreateNfaFromSymbol(EPSILON));

        auto i = 0;

        while (i < s1.size()) {
            auto x = s1[i++];
            switch (x) {
                case OP_CONCAT:
                    [[fallthrough]];
                case OP_UNION:
                    [[fallthrough]];
                case OP_PLUS:
                    [[fallthrough]];
                case OP_OPTIONAL:
                    [[fallthrough]];
                case OP_CLOSURE: {
                    // 如栈内有待运算的，且栈顶优先级较高，先计算、再入栈
                    auto op = static_cast<Op>(x);
                    while (!op_stack.empty() &&
                           IsCalculationOperator(op_stack.top()) &&
                           GetOperatorPriority(op_stack.top()) >=
                               GetOperatorPriority(op)) {
                        Calc(nfa_stack, op_stack);
                    }
                    op_stack.push(op);
                }; break;
                case OP_LEFT_PAIR:
                    // 左括号入栈
                    op_stack.push(static_cast<Op>(x));
                    break;
                case OP_RIGHT_PAIR: {
                    // 右括号闭合，优先级最高, 先计算括号内所有运算
                    while (!op_stack.empty() &&
                           op_stack.top() != OP_LEFT_PAIR) {
                        Calc(nfa_stack, op_stack);
                    }
                    // 弹出左括号
                    op_stack.pop();
                }; break;
                case OP_RANGE_START: {
                    // 解析范围, 例如 [a-zA-Z]
                    std::vector<range> ranges;
                    // 当前开始的范围
                    C range_start = EPSILON;

                    while (s1[i] != OP_RANGE_END && i < s1.size()) {
                        x = s1[i++];
                        if (x != OP_RANGE_TO) {
                            if (range_start == EPSILON)
                                range_start = x;
                            else {
                                ranges.push_back(
                                    std::make_pair(range_start, x));
                                range_start = EPSILON;
                            }
                        }
                    }
                    nfa_stack.push(CreateNfaFromRanges(ranges));
                } break;
                case OP_RANGE_END:  // 跳过右方括号
                    break;
                case '\\':  // 支持转义
                    x = s1[i++];
                    [[fallthrough]];  // 默认就转义到下一个字符
                default:
                    // 待计算的符号
                    nfa_stack.push(CreateNfaFromSymbol(x));
                    break;
            }
        }
        // 计算完可能剩余的部分
        while (!op_stack.empty()) {
            Calc(nfa_stack, op_stack);
        }
        return nfa_stack.pop();
    };
};

class DfaState : public State {
   public:
    // Set of DfaState pointers.
    typedef std::set<std::shared_ptr<DfaState>, State::PtrCmp> Set;

    // 非空边跳转表: Char => DfaState pointer.
    typedef std::unordered_map<C, std::shared_ptr<DfaState>> Table;

    DfaState(int id, bool is_end) : State(id, is_end){};

    const Table& Transitions() const { return transitions; };

    // 返回跳转的目标状态
    std::shared_ptr<DfaState> Next(C c) const {
        // 找不到此符号的跳转边, 则返回 nullptr
        if (transitions.find(c) == transitions.end()) return nullptr;
        return transitions.at(c);
    }
    void AddTransition(C c, const std::shared_ptr<DfaState>& to) {
        transitions[c] = to;
    }

    // 实现比较操作符
    bool operator==(const DfaState& st) const { return Id() == st.Id(); }
    bool operator!=(const DfaState& st) const { return Id() != st.Id(); }

   private:
    Table transitions;
};

class Dfa {
   public:
    std::shared_ptr<DfaState> start = nullptr;
    DfaState::Set states;  // 状态集合

    Dfa(std::shared_ptr<DfaState> start) : start(start){};

    // 返回状态的个数
    std::size_t Size() const { return states.size(); }
    // 返回状态列表，可被修改
    DfaState::Set& States() { return states; };
    // 是否含有状态 s?
    bool HasState(const std::shared_ptr<DfaState>& s) {
        return states.find(s) != states.end();
    };
    // 过滤终态到给定的 Set 容器中
    void EndStates(DfaState::Set& x) {
        for (auto s : states) {
            if (s->IsEnd()) x.insert(s);
        }
    };
    // 匹配一个输入的字符串
    bool Match(std::string s) {
        auto st = start;
        for (auto& c : s) {
            auto to = st->Next(c);
            if (to == nullptr) return false;
            st = to;
        }
        // 到达终态即匹配
        return st->IsEnd();
    }
};

class DfaBuilder {
   private:
    // 要处理的 NFA
    std::shared_ptr<Nfa> nfa;
    // 记录每个 DfaState 接受的非空符号 到 目标 NfaState 列表的映射
    // DfaState id => { C => NfaState set }
    std::unordered_map<int, NfaState::Table> d;
    // 缓存已经生成过的 DfaState.
    std::unordered_map<int, std::shared_ptr<DfaState>> states;

    // 从一批 NfaState 构造 DfaState 的 ID 号
    // Hash("1,2,3,...")
    int MakeDfaStateId(const NfaState::Set& N) {
        // 构造状态标号 hash("1,2,3,4,5")
        // std::set 本身是有序的, 不必排序即可拼接
        std::string str;
        for (auto& s : N) str += "," + std::to_string(s->Id());
        return std::hash<std::string>{}(str);
    }

    // 从一批 NfaState 创建一个 DfaState.
    std::shared_ptr<DfaState> MakeDfaState(const NfaState::Set& N, int id = 0) {
        if (!id) id = MakeDfaStateId(N);

        // 只要有一个是终态，DfaState 就算做终态
        bool is_end = false;
        for (auto& s : N) {
            if (s->IsEnd()) {
                is_end = true;
                break;
            }
        }

        // 记录可以由非空边跳转到的 NfaState 列表
        for (auto& s : N) {
            for (auto& p : s->Transitions()) {
                auto& c = p.first;    // 符号
                auto& st = p.second;  // 符号的目标 NfaState 状态集合
                if (c != EPSILON) {
                    d[id][c].insert(st.begin(), st.end());  // Union
                }
            }
        }
        auto st = std::make_shared<DfaState>(id, is_end);
        states[id] = st;
        return st;
    };

    // 输入一批 NfaState 状态集合 N , 只沿空边进行原地扩张
    // 采用深度优先遍历.
    void EpsilonClosure(NfaState::Set& N) {
        // 将 N 中的所有元素入栈
        stack<std::shared_ptr<NfaState>> stack;
        for (auto s : N) stack.push(s);

        // DFS 深度优先遍历
        while (!stack.empty()) {
            auto s = stack.pop();
            // 沿着空边，找所有可以到达的状态，加入集合
            if (!s->AcceptC(EPSILON)) continue;  // 找不到空边
            for (auto& t : s->Nexts(EPSILON)) {
                if (N.find(t) == N.end()) {  // t 不在 N 中
                    // 加入并压入栈
                    N.insert(t);
                    stack.push(t);
                }
            }
        }
    };

    // 返回从状态 S 经过非空边 c 跳转到的目标状态
    std::shared_ptr<DfaState> Move(const std::shared_ptr<DfaState>& S, C c) {
        // 经过符号 c 到达的目标状态集合
        auto N = d.at(S->Id()).at(c);
        // 扩张
        EpsilonClosure(N);

        // 构造 DfaState
        auto id = MakeDfaStateId(N);
        if (states.find(id) == states.end()) {
            // 不存在，才新建
            MakeDfaState(N, id);
        }
        return states.at(id);
    };

   public:
    DfaBuilder(const std::shared_ptr<Nfa>& nfa) : nfa(nfa){};
    // 将 Nfa 转换为 Dfa
    std::shared_ptr<Dfa> Build() {
        // 初始状态: 从 NFA 的开始状态沿空边可达的整个闭包
        auto N0 = NfaState::Set{nfa->start};
        EpsilonClosure(N0);
        auto S0 = MakeDfaState(N0);

        // q 是待处理的队列，先进先出，也即广度优先
        // 所谓 "处理", 就是给每个 DfaState S 填写非空边的跳转表
        std::queue<std::shared_ptr<DfaState>> q;
        q.push(S0);

        // qd 是已经在队列中的所有状态的 ID
        // 如果已经加入到队列了，就不必重复加入了
        // 实际上 q 是一种 unique 队列
        DfaState::Set qd;
        qd.insert(S0);

        // 最终要构建的 DFA, 初始状态 S0
        auto dfa = std::make_shared<Dfa>(S0);

        while (!q.empty()) {
            auto S = q.front();
            q.pop();
            qd.erase(S);

            // 对于每一个可能的 **非空** 跳转边
            auto id = S->Id();

            if (d.find(id) != d.end()) {
                for (auto& p : d.at(id)) {
                    auto& c = p.first;
                    // 跳入的是一个其他状态 T
                    auto T = Move(S, c);

                    // 记录跳转边
                    S->AddTransition(c, T);

                    // T 尚未打标，加入队列
                    if (!dfa->HasState(T) && qd.find(T) == qd.end()) {
                        q.push(T);
                        qd.insert(T);
                    };
                }
            }

            // S 已处理完成，放入 dfa
            dfa->States().insert(S);
        }
        return dfa;
    };
};

// DfaMinifier 是 DFA 化简器
class DfaMinifier {
   private:
    // 化简过程中的状态小组, 是对 std::set 的一层包装
    // Group 一旦初始化，不可再更改其内容, 类似 frozenset.
    class Group {
       public:
        // 用于比较两个 Group 的 Comparator
        // GroupSet 的元素是 pointer, 所以要实现一个 PtrCmp 结构
        class PtrCmp {
           public:
            bool operator()(const std::shared_ptr<Group>& a,
                            const std::shared_ptr<Group>& b) const {
                return a->Id() < b->Id();
            };
        };

        // 用于计算 Group* 的 Hash.
        // 这样 Group 可以作为 map 的 Key.
        class PtrHash {
           public:
            std::size_t operator()(
                const std::shared_ptr<Group>& g) const noexcept {
                return std::hash<int>{}(g->Id());
            }
        };

        // 采用左值集合构造, 走复制
        Group(const DfaState::Set& g1) : g(g1) { initId(); };

        // 采用右值集合构造: 走内容 swap
        Group(DfaState::Set&& g1) noexcept {
            g.swap(g1);
            initId();
        };

        int Id() const { return id; };

        // 是否包含终态?
        bool HasEndState() const {
            for (auto& st : g) {
                if (st->IsEnd()) return true;
            }
            return false;
        }

        const DfaState::Set& Set() const { return g; };

        // 实现比较操作符
        bool operator==(const Group& g1) const { return g1.Id() == id; }
        bool operator!=(const Group& g1) const { return g1.Id() != id; }

       private:
        DfaState::Set g;
        int id;

        void initId() {
            // id 设置为 hash(DfaState.id list ...)
            // Set 本身是有序的，所以不必排序
            std::string s;
            for (auto& st : g) s += "," + std::to_string(st->Id());
            id = std::hash<std::string>{}(s);
        }
    };

    // Dfa 化简过程中的所有分组的集合
    typedef std::set<std::shared_ptr<Group>, Group::PtrCmp> GroupSet;

    // 要化简的 DFA
    std::shared_ptr<Dfa> dfa;

    // d 记录一个 DfaState 在哪个 Group 中
    // DfaState Id => Group
    std::unordered_map<int, std::shared_ptr<Group>> d;

    // 新建一个 Group (同时支持右值的完美转发)
    std::shared_ptr<Group> MakeGroup(DfaState::Set&& states) {
        auto g = std::make_shared<Group>(std::forward<DfaState::Set>(states));
        // 记录状态归属关系
        for (auto& s : g->Set()) d[s->Id()] = g;
        return g;
    }

    // 查询一个 DfaState 目前所在的分组
    std::shared_ptr<Group> GroupOf(const std::shared_ptr<DfaState>& s) const {
        // 在任何一个时刻, 任何一个 DfaState 必然属于一个分组
        return d.at(s->Id());
    }

    // 清理死状态, 即非终态但是没有任何出边的状态
    void RemoveDeadStates() {
        auto new_states = new DfaState::Set;
        new_states->insert(dfa->start);

        for (auto st : dfa->States()) {
            // 跳过没有出边的非终态
            if (!st->IsEnd() && st->Transitions().empty()) continue;
            new_states->insert(st);
        }

        // 重写 dfa states.
        dfa->States().swap(*new_states);
        delete new_states;
    };

    // 清理无法到达的状态 (dfs)
    void RemoveUnreachableStates() {
        auto reachable = new DfaState::Set;
        reachable->insert(dfa->start);

        stack<std::shared_ptr<DfaState>> stack;
        stack.push(dfa->start);

        while (!stack.empty()) {
            auto st = stack.pop();
            for (auto& p : st->Transitions()) {
                auto& target = p.second;  // 可到达的目标状态
                if (reachable->find(target) == reachable->end()) {
                    // 不在已发现的目标中，则加入，并入栈
                    stack.push(target);
                    reachable->insert(target);
                }
            }
        }
        // 重写 dfa states.
        dfa->States().swap(*reachable);
        delete reachable;
    }

    // refine 函数的子过程
    // 在小组 g 中找到和 a 不等价的所有其他状态 b 的集合 g2
    // 如果不存在，返回的就是 nullptr
    std::shared_ptr<Group> FindDistinguishable(
        const std::shared_ptr<Group>& g, const std::shared_ptr<DfaState>& a) {
        // x 记录 distinguishable DfaStates.
        // 采用堆上内存，以在 MakeGroup 时交换指针
        auto x = new DfaState::Set;

        for (auto& p : a->Transitions()) {
            // 对于 a 有出边的情况, 考察每个出边所到达的目标状态
            auto c = p.first;
            auto ta = p.second;
            // 检查同小组的每个其他状态 b
            for (auto b : g->Set()) {
                if (*b != *a) {  // 注意比较的是对象本身, 不是指针
                    // tb 是 b 在此符号下的目标状态, 注意可能是 null
                    auto tb = b->Next(c);
                    if (tb == nullptr || *GroupOf(ta) != *GroupOf(tb)) {
                        // 目标状态所在小组不同, 记录一下
                        x->insert(b);
                    }
                }
            }

            if (!x->empty()) {
                // 对于一个出边，可以区分，就直接 break
                break;
            }
        }

        // 不存在，返回 nullptr
        if (x->empty()) {
            delete x;
            return nullptr;
        }

        auto gp = MakeGroup(std::move(*x));
        delete x;
        return gp;
    }

    // 检查 gs 中的每个分组 g:
    // 如果 g 中, 对于某个出边 ch, 存在两个状态 a, b, 其目标状态不在同一个小组中
    // 则对 g 进行切分.
    // 返回是否发生了分割
    bool Refine(GroupSet& gs) {
        for (auto g : gs) {
            // 检查每个小组
            for (auto a : g->Set()) {
                // 找到小组内与 a 不同的状态集
                auto g2 = FindDistinguishable(g, a);

                if (g2 != nullptr) {
                    // 执行切分

                    // g1 是 g 中去除 g2 的部分
                    auto x = new DfaState::Set;
                    set_sub(g->Set(), g2->Set(), *x);
                    auto g1 = MakeGroup(std::move(*x));
                    delete x;

                    // 加入新的小组，移除老的小组
                    gs.erase(g);
                    gs.insert(g1);
                    gs.insert(g2);
                    return true;
                }
            }
        }
        return false;
    }

    // minify 的子过程
    // 最终从 Group 列表再构造一个新的 DfaState 集合和跳转表，重写 DFA
    void RewriteDfa(GroupSet& gs) {
        // group => new dfa state 的映射
        std::unordered_map<std::shared_ptr<Group>, std::shared_ptr<DfaState>,
                           Group::PtrHash>
            d;

        // 新建的 state 集合
        // 在堆上申请，以避免后续内存拷贝, 而可以采用 swap
        auto new_states = new DfaState::Set;

        // 先创建一轮 state
        for (auto g : gs) {
            auto st = std::make_shared<DfaState>(g->Id(), g->HasEndState());
            new_states->insert(st);
            d[g] = st;
        }

        // 维护一下跳转关系
        for (auto g : gs) {
            for (auto s : g->Set()) {
                for (auto p : s->Transitions()) {
                    auto c = p.first;      // 跳转字符
                    auto t = p.second;     // 目标状态
                    auto gt = GroupOf(t);  // 目标状态所在的分组
                    auto st = d[gt];       // 目标状态的新 DfaState

                    // 对每个字符，目标跳转状态就是每个目标 DfaState
                    // 所在分组对应的新建的 DfaState
                    d[g]->AddTransition(c, st);
                }
            }
        }

        // 原来起始状态所在分组目前的对应状态就是新的起始状态
        dfa->start = d[GroupOf(dfa->start)];

        // 因为 new_states 是一个栈上局部变量
        dfa->States().swap(*new_states);
        delete new_states;
    }

    // 初始分组，终态单独成组，其他的成一组
    void InitGroupSet(GroupSet& gs) {
        // 所有终态分组
        auto ends = new DfaState::Set;
        dfa->EndStates(*ends);
        auto g1 = MakeGroup(std::move(*ends));
        delete ends;

        // 其他一组
        auto others = new DfaState::Set;
        set_sub(dfa->States(), g1->Set(), *others);
        auto g2 = MakeGroup(std::move(*others));
        delete others;

        gs.insert({g1, g2});
    }

   public:
    // 构造函数
    DfaMinifier(std::shared_ptr<Dfa> dfa) : dfa(dfa){};

    // 采用 Hopcroft 算法原地压缩 DFA
    void Minify() {
        RemoveUnreachableStates();
        RemoveDeadStates();

        auto original_size = dfa->Size();

        if (dfa->Size() > 1) {
            GroupSet gs;
            InitGroupSet(gs);
            // 不断分割，直到无法分割
            while (Refine(gs)) {
            }
            // 重写 DFA
            RewriteDfa(gs);
        }

        std::cout << "Minified from " << original_size << " to " << dfa->Size()
                  << std::endl;
    }
};

// Compile 把一个字符串格式的正则表达式编译成为一个 DFA
static std::shared_ptr<Dfa> Compile(const std::string& s) {
    auto nfa = NfaParser().Parse(s);
    auto dfa = DfaBuilder(nfa).Build();
    DfaMinifier(dfa).Minify();
    return dfa;
}

};  // namespace regexp
#endif
