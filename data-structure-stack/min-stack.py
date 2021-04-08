# 数据结构 - 最小栈 - 在栈的基础上，实现一个常数时间的最小值函数
# https://writings.sh/post/monotonous-stack-and-monotonous-queue
# https://leetcode-cn.com/problems/min-stack/
# 要求 Push() Pop() Min() 三个函数平均时间复杂度 O(1)


class MinStack:
    """采用两个栈来实现最小栈，要求 O(1) 时间获取最小值

    一个栈 a 是先进后出栈
    一个是 b 单调递减栈

    """

    def __init__(self):
        self.a = []  # 先进后出栈
        self.b = []  # 单调递减栈

    def push(self, value):
        if len(self.b) == 0 or value <= self.b[-1]:
            self.b.append(value)
        self.a.append(value)

    def pop(self):
        if len(self.a) <= 0:
            return -1
        value = self.a.pop()
        if value == self.b[-1]:
            self.b.pop()
        return value

    def min(self):
        if len(self.a) <= 0:
            return -1
        return self.b[-1]


def main():
    s = MinStack()
    s.push(3)
    s.push(2)
    s.push(5)
    s.push(1)
    assert s.min() == 1
    assert s.pop() == 1
    assert s.min() == 2
    assert s.pop() == 5
    assert s.min() == 2


if __name__ == "__main__":
    main()
