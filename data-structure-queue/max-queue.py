# 最大值队列 - 在队列的基础上，实现一个常数时间的最大值函数
# https://writings.sh/post/monotonous-stack-and-monotonous-queue
# https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/
# 要求 PushBack() PopFront() Max() 三个函数平均时间复杂度 O(1)


class MaxQueue:
    """两个队列实现最大值队列，要求 O(1) 时间返回最大值

    队列 a 是正常的先进先出队列
    队列 b 是单调递减双端队列
    """

    def __init__(self):
        self.a = []  # FIFO 队列
        self.b = []  # 单调递减队列

    def push_back(self, value):
        self.a.append(value)
        while len(self.b) > 0 and self.b[-1] < value:
            self.b.pop()
        self.b.append(value)

    def pop_front(self):
        if len(self.a) <= 0:
            return -1
        value = self.a.pop(0)

        if value == self.b[0]:
            self.b.pop(0)
        return value

    def max(self):
        if len(self.b) <= 0:
            return -1
        return self.b[0]


###
# 测试
###


def main():
    q = MaxQueue()
    q.push_back(1)
    q.push_back(4)
    q.push_back(3)
    q.push_back(2)
    assert q.max() == 4
    assert q.pop_front() == 1
    assert q.pop_front() == 4
    assert q.max() == 3


if __name__ == "__main__":
    main()
