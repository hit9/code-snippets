#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

// std::stack 不好用，这里封一个简单的 wrapper
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

// 符号
typedef char C;

// 空符号
static C EPSILON = '\0';

// 操作符
enum Op : C {
    OP_CONCAT = '&',
    OP_UNION = '|',
    OP_CLOSURE = '*',
    OP_LEFT_PAIR = '(',
    OP_RIGHT_PAIR = ')',
};

// 是否是运算符
bool IsCalculationOperator(C c) {
    switch (c) {
        case OP_CONCAT:
            return true;
        case OP_UNION:
            return true;
        case OP_CLOSURE:
            return true;
        default:
            return false;
    }
}

// 运算符优先级
int GetOperatorPriority(Op op) {
    switch (op) {
        case OP_CONCAT:
            return 1;
        case OP_UNION:
            return 1;
        case OP_CLOSURE:
            return 2;
        default:
            return 0;
    };
}

// 是否一个存在对右侧字符有作用的操作符 (重载)
bool IsRightActingOperator(C c) {
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
bool IsAbleInsertConcat(C c) {
    switch (c) {
        case OP_CONCAT:
            [[fallthrough]];
        case OP_UNION:
            [[fallthrough]];
        case OP_CLOSURE:
            [[fallthrough]];
        case OP_RIGHT_PAIR:
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
    State(int id, bool is_end) : id(id), is_end(is_end){};
    int Id() const { return id; };
    bool IsEnd() const { return is_end; };
};

// 用于比较两个状态的 Comparator
class StateComparator {
   public:
    bool operator()(const std::shared_ptr<State> a,
                    const std::shared_ptr<State> b) const {
        return a->Id() < b->Id();
    };
};

class NfaState : public State {
   public:
    typedef std::set<std::shared_ptr<NfaState>, StateComparator> Set;
    typedef std::unordered_map<C, Set> Table;

    NfaState(int id, bool is_end) : State(id, is_end){};
    const Table& Transitions() const { return transitions; };
    void AddTransition(C c, const std::shared_ptr<NfaState> to) {
        transitions[c].insert(to);
        // 不在能成为终态
        if (is_end) is_end = false;
    }

   private:
    Table transitions;
};

class Nfa {
   public:
    std::shared_ptr<NfaState> start = nullptr;
    std::shared_ptr<NfaState> end = nullptr;
    Nfa(std::shared_ptr<NfaState> start, std::shared_ptr<NfaState> end)
        : start(start), end(end){};
};

// 从 Regexp 字符串构造 Nfa 自动机
class NfaParser {
    // 待运算的 Nfa 栈
    typedef stack<std::shared_ptr<Nfa>> NfaStack;
    // 待运算的运算符栈
    typedef stack<Op> OpStack;

   private:
    // 状态计数器
    int state_no = 0;

    // 新建一个 NfaState.
    std::shared_ptr<NfaState> NewState(bool is_end) {
        // TODO 如何 free NfaState 的问题
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
    // 连接两个 Nfa
    //    a: 1 -> 2
    //    b: 3 -> 4
    //               e
    //    ab: 1 -> 2 -> 3 -> 4
    std::shared_ptr<Nfa> NfaConcat(std::shared_ptr<Nfa> a,
                                   std::shared_ptr<Nfa> b) {
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
    std::shared_ptr<Nfa> NfaUnion(std::shared_ptr<Nfa> a,
                                  std::shared_ptr<Nfa> b) {
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
    std::shared_ptr<Nfa> NfaClosure(std::shared_ptr<Nfa> a) {
        auto start = NewState(false);              // 3
        auto end = NewState(true);                 // 4
        a->end->AddTransition(EPSILON, a->start);  // 2->1
        start->AddTransition(EPSILON, a->start);   // 3->1
        a->end->AddTransition(EPSILON, end);       // 2->4
        start->AddTransition(EPSILON, end);        // 3->4
        return std::make_shared<Nfa>(start, end);
    };

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
            default:
                break;
        }
    }

    // 规整输入字符串, 在相邻符号间插入 & 符号
    // e.g. 'ab|c' => 'a&b|c'
    //     'a*c' => 'a*&c'
    //     '(a)b' => '(a)&b'
    //     'a(ab)' => 'a&(a&b)'
    std::string Normalize(const std::string& s) {
        std::string s1;
        for (auto& c : s) {
            if (IsAbleInsertConcat(c) && !s1.empty() &&
                !IsRightActingOperator(s1.back())) {
                // 可以插入 & 符号,
                // 并且前一个符号有向右贴合的作用，那么可以插入连接符
                s1.push_back(OP_CONCAT);
            }
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
    typedef std::unordered_map<C, std::shared_ptr<DfaState>> Table;

    DfaState(int id, bool is_end) : State(id, is_end){};

    const Table& Transitions() const { return transitions; };
    // 返回跳转的目标状态
    std::shared_ptr<DfaState> Next(C c) const {
        // 找不到此符号的跳转边, 则返回 nullptr
        if (transitions.find(c) == transitions.end()) return nullptr;
        return transitions.at(c);
    }
    void AddTransition(C c, std::shared_ptr<DfaState> to) {
        transitions[c] = to;
    }

   private:
    Table transitions;
};

class Dfa {
    typedef std::set<std::shared_ptr<DfaState>, StateComparator> Set;

   public:
    std::shared_ptr<DfaState> start = nullptr;
    Set states;  // 状态集合

    Dfa(std::shared_ptr<DfaState> start) : start(start){};
    std::size_t Size() const { return states.size(); }
    Set& States() { return states; };
    bool HasState(std::shared_ptr<DfaState> s) {
        return states.find(s) != states.end();
    }

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
        // 新建一个 vector 将 NfaState 按标号排序
        std::vector v(N.begin(), N.end());
        std::sort(v.begin(), v.end(),
                  [](auto a, auto b) { return a->Id() < b->Id(); });

        // 构造状态标号 hash("1,2,3,4,5")
        std::string str;
        for (auto& s : v) str += "," + std::to_string(s->Id());
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
                auto& st = p.second;  //  符号的目标 NfaState 状态集合
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
            auto& transitions = s->Transitions();
            auto it = transitions.find(EPSILON);
            if (it == transitions.end()) continue;  // 找不到空边
            for (auto& t : it->second) {
                if (N.find(t) == N.end()) {  // t 不在 N 中
                    // 加入并压入栈
                    N.insert(t);
                    stack.push(t);
                }
            }
        }
    };

    // 返回从状态 S 经过非空边 c 跳转到的目标状态
    std::shared_ptr<DfaState> Move(std::shared_ptr<DfaState> S, C c) {
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
    DfaBuilder(std::shared_ptr<Nfa> nfa) : nfa(nfa){};
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

        // 最终要构建的 DFA
        auto dfa = std::make_shared<Dfa>(S0);

        while (!q.empty()) {
            auto S = q.front();
            q.pop();

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
                    if (!dfa->HasState(T)) q.push(T);
                }
            }

            // S 已处理完成，放入 dfa
            dfa->States().insert(S);
        }

        return dfa;
    };
};

int main(void) {
    auto nfa = NfaParser().Parse("a(a|b)*c(d|e)(x|y|z)*");
    auto dfa = DfaBuilder(nfa).Build();
    std::cout << dfa->Match("aabbace") << std::endl;
    std::cout << dfa->Match("aabbbbbbace") << std::endl;
    std::cout << dfa->Match("aabbbbbbacd") << std::endl;
    std::cout << dfa->Match("aabbbbbbad") << std::endl;
    return 0;
}
