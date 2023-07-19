"""
实现一个简单的正则表达式引擎 (Python 版本)

支持的操作符:
    连接 ab
    克林闭包 a*
    取并 a|b
"""

Symbol = str  # 正则符号
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
    """NFA 状态, 一个数字可以表达"""

    def __init__(self, no: int, is_end: bool):
        self.no = no
        self.is_end = is_end
        # 跳转表, { Symbol => { Target States...}}
        self.transitions: dict[Symbol, set["NfaState"]] = {}

    def add_transition(self, symbol: Symbol, to: "NfaState"):
        self.transitions.setdefault(symbol, set()).add(to)
        if self.is_end:
            self.is_end = False

    def __hash__(self) -> int:
        return hash(self.no)

    def __repr__(self) -> str:
        return str(self.no)


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

    def create_nfa_from_symbol(self, symbol: Symbol) -> Nfa:
        """
              symbol
        start ------> end
        """
        start = self.new_state(False)
        end = self.new_state(True)
        start.add_transition(symbol, end)
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
        print(s)

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
    """DFA 的一个状态是多个 Nfa 状态的集合"""

    def __init__(self, nfa_states: set[NfaState]):
        # NFA 状态集合
        self.nfa_states = frozenset(nfa_states)

        # 是否终态: 但凡有含义 NfaState 终态
        self.is_end = False
        for s in nfa_states:
            if s.is_end:
                self.is_end = True
                break

        # 非空跳转 { Symbol => { NfaStates...}}
        self.nfa_transitions: dict[Symbol, set[NfaState]] = {}
        for s in nfa_states:
            for symbol, targets in s.transitions.items():
                if symbol != epsilon:  # 只关注非空边跳转
                    self.nfa_transitions.setdefault(symbol, set())
                    self.nfa_transitions[symbol] |= targets

    def __hash__(self) -> int:
        return hash(self.nfa_states)

    def __eq__(self, o: object) -> bool:
        return isinstance(o, DfaState) and hash(self) == hash(o)

    def __repr__(self) -> str:
        return repr(self.nfa_states)


class Dfa:
    def __init__(self, start: DfaState):
        self.start = start
        # 跳转表 { from_state => { symbol => to_state } }
        self.transitions: dict[DfaState, dict[Symbol, DfaState]] = {}

    def add_transition(self, from_: DfaState, symbol: Symbol, to: DfaState):
        self.transitions.setdefault(from_, {})[symbol] = to

    def match(self, s: str) -> bool:
        """匹配一个字符串"""
        st = self.start
        for x in s:
            if st not in self.transitions:
                return False
            if x not in self.transitions[st]:
                return False
            st = self.transitions[st][x]
        return st.is_end


class DfaBuilder:
    def epsilon_closure(self, S: DfaState | set[NfaState]) -> DfaState:
        """
        输入 DFA 的状态 S, 计算 S 中每个状态 s 可以只沿空边 epsilon 到达的状态集合 T.:
        采用深度优先遍历.
        """
        # 要计算的结果集合, 初始化为输入的 S
        T = set(S.nfa_states) if isinstance(S, DfaState) else S

        # S 中的所有 NfaState 入栈
        stack = []
        for s in T:
            stack.append(s)

        # DFS 深度优先遍历
        while stack:
            s = stack.pop()
            # 沿着空边，找所有可以到达的状态，加入 T
            for t in s.transitions.get(epsilon, set()):
                if t not in T:
                    T.add(t)
                    # 压入栈中
                    stack.append(t)
        return DfaState(T)

    def move(self, S: DfaState, symbol: Symbol) -> DfaState:
        """move(S, symbol) 记录一个非空边跳转到的目标 DfaState"""
        return DfaState(S.nfa_transitions[symbol])

    def from_nfa(self, nfa: Nfa) -> Dfa:
        """
        将 NFA 转化为 DFA
        """
        # 初始状态: 从 NFA 的开始状态沿空边可达的整个闭包
        S0 = self.epsilon_closure({nfa.start})

        # q 是待处理的队列，先进先出，也即广度优先
        q = [S0]

        # 最终要构建的 DFA
        dfa = Dfa(S0)

        # 标记过的状态
        x = set()

        while q:
            # 弹出一个待处理的状态 S
            S = q.pop(0)

            # 对于每一个可能的非空跳转边 symbol
            for symbol in S.nfa_transitions:

                # TODO: 如何避免 epsilon_closure 的重复计算?
                # 跳入的是一个其他状态 T
                T = self.epsilon_closure(self.move(S, symbol))
                if T not in x:
                    # T 尚未打标，加入队列
                    q.append(T)

                # 记录跳转边
                dfa.add_transition(S, symbol, T)

            # S 打标
            x.add(S)
        return dfa


def compile(s: str) -> "Dfa":
    return DfaBuilder().from_nfa(NfaParser().parse(s))


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
