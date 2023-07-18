"""
实现一个简单的正则表达式引擎 (Python 版本)

支持的操作符:
    连接 ab
    克林闭包 a*
    取并 a|b
"""

Symbol = str  # 正则符号
State = int  # 状态
epsilon = ""  # 空符号

op_concat = "&"
op_union = "|"
op_closure = "*"
op_left_pair = "("
op_right_pair = ")"

# 运算符 => 优先级
OPS = {
    op_concat: 1,
    op_union: 1,
    op_closure: 2,
}


def is_symbol(x: str) -> bool:
    return x not in {op_concat, op_union, op_closure, op_left_pair, op_right_pair}


class nfa:
    """运算过程中使用的小 NFA, 跳转表都基于大 NFA 的"""

    def __init__(self, start: State, end: State):
        self.start = start
        self.end = end


class Nfa:
    def __init__(self):
        self.start = None
        self.end = None
        # 跳转表 { from_state => { symbol => { to_state, ... } } }
        self.transitions = {}
        self._state_seq = 0  # 状态计数

    def new_state(self) -> State:
        self._state_seq += 1
        return State(self._state_seq)

    def new_transition(self, from_: State, symbol: Symbol, to: State):
        self.transitions.setdefault(from_, {}).setdefault(symbol, set()).add(to)

    def create_nfa_from_symbol(self, symbol: Symbol) -> nfa:
        """
              symbol
        start ------> end
        """
        start = self.new_state()
        end = self.new_state()
        self.new_transition(start, symbol, end)
        return nfa(start, end)

    def nfa_concat(self, a: nfa, b: nfa) -> nfa:
        """
        a: 1 -> 2
        b: 3 -> 4
                   e
        ab: 1 -> 2 -> 3 -> 4
        """
        self.new_transition(a.end, epsilon, b.start)
        return nfa(a.start, b.end)

    def nfa_union(self, a: nfa, b: nfa) -> nfa:
        """
        a: 1 -> 2
        b: 3 -> 4

        a|b:
               e         e
              +-> 1 -> 2 -+
            5-+           +-> 6
              +-> 3 -> 4 -+
               e         e
        """
        start = self.new_state()  # 5
        end = self.new_state()  # 6
        self.new_transition(start, epsilon, a.start)
        self.new_transition(start, epsilon, b.start)
        self.new_transition(a.end, epsilon, end)
        self.new_transition(b.end, epsilon, end)
        return nfa(start, end)

    def nfa_closure(self, a: nfa) -> nfa:
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
        start = self.new_state()  # 3
        end = self.new_state()  # 4
        self.new_transition(a.end, epsilon, a.start)
        self.new_transition(start, epsilon, a.start)
        self.new_transition(a.end, epsilon, end)
        self.new_transition(start, epsilon, end)
        return nfa(start, end)

    def calc(self, nfa_stack: list[nfa], op_stack: list[str]):
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
        """
        chs: list[str] = []
        for x in s:
            if is_symbol(x) and chs and is_symbol(chs[-1]):
                chs.append(op_concat)
            chs.append(x)
        return "".join(chs)

    def parse(self, s: str) -> "Nfa":
        """采用 Dijkstra 双栈法进行表达式求值"""

        nfa_stack: list[nfa] = []
        op_stack: list[str] = []

        s = self.normalize(s)

        i = 0

        # 避免空串
        nfa_stack.append(self.create_nfa_from_symbol(epsilon))

        while i < len(s):
            x = s[i]
            if x in OPS:
                # 如栈内有待运算的，且栈顶优先级较高，先计算、再入栈
                while op_stack and op_stack[-1] in OPS and OPS[op_stack[-1]] >= OPS[x]:
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

        n = nfa_stack.pop()

        self.start = n.start
        self.end = n.end
        return self


class Dfa:
    def __init__(self):
        self.start = None
        self.ends = set()
        # 跳转表 { from_state => { symbol => to_state } }
        self.transitions = {}
        self._state_seq = 0

    def new_state(self) -> State:
        self._state_seq += 1
        return State(self._state_seq)

    def new_transition(self, from_: State, symbol: Symbol, to: State):
        self.transitions.setdefault(from_, {})[symbol] = to


def epsilon_closure(s: State):
    """输入 DFA 的状态 s, 计算 NFA 中能够从状态 s 只通过空边 epsilon 到达的状态集合
    采用深度优先遍历.
    """
    pass


if __name__ == "__main__":
    n = Nfa().parse("ab*((c|d)efg)*")
