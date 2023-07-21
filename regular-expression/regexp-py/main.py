"""
实现一个简单的正则表达式引擎 (Python 版本)

支持的操作符:
    连接 ab
    克林闭包 a*
    取并 a|b

核心步骤:
    NfaParser().parse()      解析正则表达式，构造 NFA
    DfaBuilder().build()     NFA 转换为 DFA
    DfaMinifier().minify()   压缩 DFA 状态数

需要 Python >= 3.7 (typing hint)
"""

from typing import Optional

C = str  # 符号
epsilon = ""  # 空符号

op_concat = "&"
op_union = "|"
op_closure = "*"
op_left_pair = "("
op_right_pair = ")"

# 运算符 => 优先级
P = {
    op_concat: 1,
    op_union: 1,
    op_closure: 2,
}


def is_right_acting_operator(x: str) -> bool:
    """是否一个存在对右侧字符有作用的操作符"""
    return x in {op_concat, op_union, op_left_pair}


def is_able_insert_concat(x: str) -> bool:
    """是否可以在 x 左侧插入 连接符?"""
    if x in {op_concat, op_union, op_closure, op_right_pair}:
        return False
    return True  # 左括号, 一般字符可以


class NfaState:
    def __init__(self, id: int, is_end: bool):
        self.id = id
        self.is_end = is_end
        # 跳转表, { C => { Target States...}}
        self.transitions: dict[C, set["NfaState"]] = {}

    def add_transition(self, ch: C, to: "NfaState"):
        self.transitions.setdefault(ch, set()).add(to)
        if self.is_end:
            self.is_end = False

    def __hash__(self) -> int:
        return hash(self.id)

    def __repr__(self) -> str:
        return str(self.id)


class Nfa:
    def __init__(self, start: NfaState, end: NfaState):
        self.start = start
        self.end = end


class NfaParser:
    """从 Regexp 构造 NFA 状态机"""

    def __init__(self):
        # 状态计数器
        self.state_no = 0

    def new_state(self, is_end: bool) -> NfaState:
        self.state_no += 1
        return NfaState(self.state_no, is_end)

    def create_nfa_from_symbol(self, ch: C) -> Nfa:
        """
                ch
        start ------> end
        """
        start = self.new_state(False)
        end = self.new_state(True)
        start.add_transition(ch, end)
        return Nfa(start, end)

    def nfa_concat(self, a: Nfa, b: Nfa) -> Nfa:
        """
        a: 1 -> 2
        b: 3 -> 4
                   e
        ab: 1 -> 2 -> 3 -> 4
        """
        a.end.add_transition(epsilon, b.start)  # 2->3
        return Nfa(a.start, b.end)

    def nfa_union(self, a: Nfa, b: Nfa) -> Nfa:
        """
        a: 1 -> 2
        b: 3 -> 4

        a|b:
               e         e
              +-> 1 -> 2 -+
           5->+           +-> 6
              +-> 3 -> 4 -+
               e         e
        """
        start = self.new_state(False)  # 5
        end = self.new_state(True)  # 6
        start.add_transition(epsilon, a.start)  # 5->1
        start.add_transition(epsilon, b.start)  # 5->3
        a.end.add_transition(epsilon, end)  # 2->6
        b.end.add_transition(epsilon, end)  # 4->6
        return Nfa(start, end)

    def nfa_closure(self, a: Nfa) -> Nfa:
        """
        a: 1->2
        a*:
                   e
                 +----+
              e  V    | e
            3 -> 1 -> 2 -> 4
            |              ^
            +--------------+
                    e
        """
        start = self.new_state(False)  # 3
        end = self.new_state(True)  # 4
        a.end.add_transition(epsilon, a.start)  # 2->1
        start.add_transition(epsilon, a.start)  # 3->1
        a.end.add_transition(epsilon, end)  # 2->4
        start.add_transition(epsilon, end)  # 3->4
        return Nfa(start, end)

    def calc(self, nfa_stack: list[Nfa], op_stack: list[str]):
        if not op_stack:
            return
        op = op_stack.pop()
        if op == op_closure:
            a = nfa_stack.pop()
            nfa_stack.append(self.nfa_closure(a))
        elif op == op_concat:
            b = nfa_stack.pop()
            a = nfa_stack.pop()
            nfa_stack.append(self.nfa_concat(a, b))
        elif op == op_union:
            b = nfa_stack.pop()
            a = nfa_stack.pop()
            nfa_stack.append(self.nfa_union(a, b))

    def normalize(self, s: str) -> str:
        """规整输入字符串, 在相邻符号间插入 & 符号
        e.g. 'ab|c' => 'a&b|c'
            'a*c' => 'a*&c'
            '(a)b' => '(a)&b'
            'a(ab)' => 'a&(a&b)'
        """
        chs: list[str] = []
        for x in s:
            if (
                is_able_insert_concat(x)
                # 并且前一个符号没有向右贴合的作用，那么可以插入连接符
                and chs
                and not is_right_acting_operator(chs[-1])
            ):
                chs.append(op_concat)

            chs.append(x)
        return "".join(chs)

    def parse(self, s: str) -> Nfa:
        """采用 Dijkstra 双栈法进行表达式求值"""

        nfa_stack: list[Nfa] = []
        op_stack: list[str] = []

        s = self.normalize(s)
        print("normalized to:", s)

        i = 0

        # 避免空串
        nfa_stack.append(self.create_nfa_from_symbol(epsilon))

        while i < len(s):
            x = s[i]
            if x in P:
                # 如栈内有待运算的，且栈顶优先级较高，先计算、再入栈
                while op_stack and op_stack[-1] in P and P[op_stack[-1]] >= P[x]:
                    self.calc(nfa_stack, op_stack)
                op_stack.append(x)
            elif x == op_left_pair:  # 左括号入栈
                op_stack.append(x)
            elif x == op_right_pair:
                # 右括号闭合，优先级最高, 先计算括号内所有运算
                while op_stack and op_stack[-1] != op_left_pair:
                    self.calc(nfa_stack, op_stack)
                op_stack.pop()  # 弹出左括号
            else:
                # 待计算的符号
                nfa_stack.append(self.create_nfa_from_symbol(x))
            i += 1

        # 计算完可能剩余的部分
        while op_stack:
            self.calc(nfa_stack, op_stack)

        return nfa_stack.pop()


class DfaState:
    def __init__(self, id: str, is_end: bool) -> None:
        self.id = id
        self.is_end = is_end
        self.transitions: dict[C, "DfaState"] = {}  # 跳转表

    def add_transition(self, ch: C, to: "DfaState"):
        self.transitions[ch] = to

    def __hash__(self) -> int:
        return hash(self.id)

    def __eq__(self, o: object) -> bool:
        return isinstance(o, DfaState) and hash(self) == hash(o)

    def __repr__(self) -> str:
        return self.id


class Dfa:
    def __init__(self, start: DfaState):
        self.start = start
        self.states: set[DfaState] = set()

    def size(self) -> int:
        return len(self.states)

    def match(self, s: str) -> bool:
        """匹配一个字符串"""
        st = self.start
        for x in s:
            if x not in st.transitions:
                return False
            st = st.transitions[x]
        return st.is_end


class DfaBuilder:
    """从 NFA 构造 DFA"""

    def __init__(self, nfa: Nfa) -> None:
        # 要处理的 nfa
        self.nfa = nfa
        # 记录每个 DfaState 接受的非空符号 到 目标 NfaState 列表的字典
        # DfaState id => { C => NfaState set }
        self.d: dict[str, dict[C, set[NfaState]]] = {}
        # states 缓存已经生成过的 DfaState
        self.states: dict[str, DfaState] = {}

    def make_dfa_state_id(self, N: set[NfaState]) -> str:
        # 从一批 NfaState 构造 DfaState 的标号
        return ",".join(map(str, sorted(N, key=lambda x: x.id)))

    def make_dfa_state(self, N: set[NfaState], id: str = "") -> DfaState:
        """从一批 NfaState 创建一个 DfaState."""
        if not id:
            id = self.make_dfa_state_id(N)
        # 只要有一个是终态，DfaState 就算做终态
        is_end = any(s.is_end for s in N)
        # 记录可以由非空边跳转到的 NfaState 列表
        for s in N:
            for ch in s.transitions:
                if ch != epsilon:
                    self.d.setdefault(id, {})
                    self.d[id].setdefault(ch, set())
                    self.d[id][ch] |= s.transitions[ch]
        st = DfaState(id, is_end)
        self.states[id] = st
        return st

    def epsilon_closure(self, N: set[NfaState]) -> None:
        """
        输入一批 NfaState 状态集合 N , 只沿空边进行原地扩张
        采用深度优先遍历.
        """
        # N 中的所有 NfaState 入栈
        stack = []
        for s in N:
            stack.append(s)

        # DFS 深度优先遍历
        while stack:
            s = stack.pop()
            # 沿着空边，找所有可以到达的状态，加入集合
            for t in s.transitions.get(epsilon, set()):
                if t not in N:
                    N.add(t)
                    # 压入栈中
                    stack.append(t)

    def move(self, S: DfaState, ch: C) -> DfaState:
        """move(S, ch) 返回从状态 S 经过非空边 ch 跳转到的目标状态"""
        N = self.d[S.id][ch]
        # TODO: 似乎无法避免 epsilon_closure 的重复计算?
        self.epsilon_closure(N)
        id = self.make_dfa_state_id(N)
        if id not in self.states:
            # 如果已经生成过，则返回，不再新建
            self.make_dfa_state(N, id=id)
        return self.states[id]

    def build(self) -> Dfa:
        """将 NFA 转化为 DFA"""
        # 初始状态: 从 NFA 的开始状态沿空边可达的整个闭包
        N0 = {self.nfa.start}
        self.epsilon_closure(N0)
        S0 = self.make_dfa_state(N0)

        # q 是待处理的队列，先进先出，也即广度优先
        # 所谓 "处理", 就是给每个 DfaState S 填写非空边的跳转表
        q = [S0]

        # 最终要构建的 DFA
        dfa = Dfa(S0)

        while q:
            # 弹出一个待处理的状态 S
            S = q.pop(0)

            # 对于每一个可能的 **非空** 跳转边 ch
            for ch in self.d.get(S.id, {}):

                # 跳入的是一个其他状态 T
                T = self.move(S, ch)

                # 记录跳转边
                S.add_transition(ch, T)

                if T not in dfa.states:
                    # T 尚未打标，加入队列
                    q.append(T)

            # S 已处理完成，放入 dfa
            dfa.states.add(S)
        return dfa


# Dfa 化简过程中的 DFA 状态小组
DfaStateGroup = frozenset[DfaState]
# Dfa 化简过程中的所有分组的集合
DfaStateGroupSet = set[DfaStateGroup]


class DfaMinifier:
    """采用 Hopcroft 算法压缩 DFA"""

    def __init__(self, dfa: Dfa):
        self.dfa = dfa
        # d 记录一个 DfaState 在哪个 DfaStateGroup 中
        self.d: dict[str, DfaStateGroup] = {}

    def make_group(
        self, dfa_states: Optional[set[DfaState] | DfaStateGroup] = None
    ) -> DfaStateGroup:
        g = DfaStateGroup(dfa_states or set())
        # 记录每个状态归属的 group
        for s in g:
            self.d[s.id] = g
        return g

    def group(self, s: DfaState) -> DfaStateGroup:
        """返回 s 所在的小组"""
        return self.d[s.id]

    def remove_dead_states(self):
        """清理死状态: 即非终态但是没有任何出边的状态"""
        dead = set()
        for s in self.dfa.states:
            if s.is_end:
                continue
            if not s.transitions:
                dead.add(s)
        self.dfa.states -= dead

    def remove_unreachable_states(self):
        """清理无法状态的状态 (dfs)"""
        stack = [self.dfa.start]
        reachable = {self.dfa.start}
        while stack:
            s = stack.pop()
            for _, t in s.transitions.items():
                if t not in reachable:
                    stack.append(t)
                    reachable.add(t)
        self.dfa.states = reachable

    def find_distinguishable(self, g: DfaStateGroup, a: DfaState) -> DfaStateGroup:
        """refine 函数的子过程
        在小组 g 中找到和 a 不等价的所有其他状态 b 的集合 g2
        如果不存在，返回的就是空集合
        """
        x = set()
        for ch in a.transitions:
            # 对于 a 有出边的情况, 考察每个出边所到达的目标状态
            ta = a.transitions[ch]
            # 检查同小组的每个其他状态 b
            for b in g:
                if b != a:
                    # tb 是 b 在此符号下的目标状态, 注意可能是 None
                    tb = b.transitions.get(ch, None)
                    if tb is None or self.group(ta) != self.group(tb):
                        # 目标状态所在小组不同, 记录一下
                        x.add(b)
            if x:
                # 对于一个出边，可以区分，就直接 break
                break
        return self.make_group(x)

    def refine(self, gs: DfaStateGroupSet) -> bool:
        """检查 gs 中的每个分组 g:
        如果 g 中, 对于某个出边 ch, 存在两个状态 a, b, 其目标状态不在同一个小组中
        则对 g 进行切分.
        返回是否发生了分割
        """
        for g in gs:
            # 检查每个小组
            for a in g:
                # 找到小组内与 a 不同的状态集合
                g2 = self.find_distinguishable(g, a)
                if g2:
                    # 执行切分
                    g1 = self.make_group(g - g2)
                    # 加入新的小组，移除废弃的分组
                    gs.remove(g)
                    gs.add(g1)
                    gs.add(g2)
                    return True
        return False

    def _rewrite_dfa(self, gs: DfaStateGroupSet) -> None:
        """minify 的子过程
        最终从 DfaStateGroup 列表再构造一个新的 DfaState 集合和跳转表，重写 DFA
        """
        d = {}  # group => state

        # 先创建一轮 state
        for g in gs:
            d[g] = DfaState(str(hash(g)), any(s.is_end for s in g))

        # 再维护下跳转关系
        for g in gs:
            for s in g:
                for ch in s.transitions:
                    t = s.transitions[ch]
                    tg = d[self.group(t)]
                    # 对每个字符，目标跳转状态就是每个目标 DfaState
                    # 所在分组对应的新建的 DfaState
                    d[g].add_transition(ch, tg)

        self.dfa.start = d[self.group(self.dfa.start)]
        self.dfa.states = set(d.values())

    def minify(self) -> None:
        self.remove_unreachable_states()
        self.remove_dead_states()

        if self.dfa.size() > 1:
            # 初始分组, 把终态单独成组, 其他状态一组
            g1 = self.make_group({s for s in self.dfa.states if s.is_end})
            g0 = self.make_group(self.dfa.states - g1)
            gs = {g0, g1}
            # 不断分割，直到无法分割
            while self.refine(gs):
                pass
            self._rewrite_dfa(gs)

        print("minified size:", self.dfa.size())


def compile(s: str) -> "Dfa":
    """compile 将给定的正则表达式字符串编译到最小 DFA"""
    nfa = NfaParser().parse(s)
    dfa = DfaBuilder(nfa).build()
    DfaMinifier(dfa).minify()
    return dfa


if __name__ == "__main__":
    dfa = compile("a(a|b)*c(d|e)(x|y|z)*")
    print(dfa.match("aabbace"))  # True
    print(dfa.match("aabbbbbbace"))  # True
    print(dfa.match("aabbbbbbacd"))  # True
    print(dfa.match("aabbbbbbad"))  # False
    print(dfa.match("aabbbbbbaf"))  # False
    print(dfa.match("aabbbbbbacdxxx"))  # True
    print(dfa.match("aabbbbbbacdxzy"))  # True
    print(dfa.match("aabbbbbbacdxzy1"))  # False

    dfa1 = compile("aa*(b|c)*abc")
    print(dfa1.match("aababc"))  # True
    print(dfa1.match("acabc"))  # True
    print(dfa1.match("aabc"))  # True
    print(dfa1.match("aabaabc"))  # False
    print(dfa1.match("abbabc"))  # True
    print(dfa1.match("aacx"))  # False

    dfa2 = compile("abc(e|f)g*(ab)*ab")
    print(dfa2.match("abcegabab"))  # True
    print(dfa2.match("abcegababab"))  # True
    print(dfa2.match("abcfgababab"))  # True
    print(dfa2.match("abckgababab"))  # False
