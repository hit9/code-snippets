"""
倒酒问题, 也叫注水问题
有三个容器，分别可以装 4L, 7L, 10L 升水，其中 4L 和 7L 的容器是满的，10L 的容器是空的。
现在只能做一种操作：将一个容器的酒倒入另一个容器，且此操作只可以在源容器已空或者目标容器已满时终止。
目前想知道，是否存在有一个合理的倒酒顺序，使得最终 4L 和 7L 的容器都恰好各有 2L 酒？
"""


def pour_visited_matrix():
    # A, B, C 分别表示 4L, 7L, 10L 的容器
    # 共六种倒酒情况: A->B, A->C, B->C, B->A, C->A, C->B
    # a, b, c 记录每个状态下的酒的容量
    # 采用 DFS 深度优先遍历的方式，计算所有可能的状态

    # d 是访问数组，d[a][b], a, b 确定后，即可确定 c
    d = [[0] * 8] * 5

    # 起始情况，a=4, b=7, 入栈
    s = [[4, 7]]

    while len(s) > 0:
        # 获取栈顶 a, b
        a, b = s.pop(-1)
        # 推导当前第三个容器的状态
        c = 11 - a - b

        if d[a][b]:
            # 如果访问过，则不再访问
            continue

        d[a][b] = 1

        # A -> B
        if a > 0 and b < 7:
            x = min(a, 7 - b)
            a1 = a - x
            b1 = b + x
            s.append([a1, b1])
        # A -> C
        if a > 0 and c < 10:
            x = min(a, 10 - c)
            a1 = a - x
            c1 = c + x
            b1 = 11 - a1 - c1
            s.append([a1, b1])
        # B -> A
        if b > 0 and a < 4:
            x = min(b, 4 - a)
            a1 = a + x
            b1 = b - x
            s.append([a1, b1])
        # B -> C
        if b > 0 and c < 10:
            x = min(b, 10 - c)
            c1 = c + x
            b1 = b - x
            a1 = 11 - b1 - c1
            s.append([a1, b1])
        # C -> A
        if c > 0 and a < 4:
            x = min(c, 4 - a)
            a1 = a + x
            c1 = c - x
            b1 = 11 - a1 - c1
            s.append([a1, b1])
        # C -> B
        if c > 0 and b < 7:
            x = min(c, 7 - b)
            b1 = b + x
            c1 = c - x
            a1 = 11 - b1 - c1
            s.append([a1, b1])

    return d


if __name__ == "__main__":
    d = pour_visited_matrix()
    # 2,2 是否在其中?
    print(d[2][2])
