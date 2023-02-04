"""
倒酒问题, 也叫注水问题
有三个容器，分别可以装 4L, 7L, 10L 升水，其中 4L 和 7L 的容器是满的，10L 的容器是空的。
现在只能做一种操作：将一个容器的酒倒入另一个容器，且此操作只可以在源容器已空或者目标容器已满时终止。
目前想知道，是否存在有一个合理的倒酒顺序，使得最终 4L 或 7L 的容器恰好有 2L 酒？

https://writings.sh/post/pour-problem
"""

# A, B, C 分别表示 4L, 7L, 10L 的容器

# 倒酒的动作
ACTION_VOID = ""  # 空标志
ACTION_INIT = "(init)"  # 初始标志
ACTION_A_TO_B = "(A->B)"  # A容器倒入B容器，以下雷同
ACTION_A_TO_C = "(A->C)"
ACTION_B_TO_A = "(B->A)"
ACTION_B_TO_C = "(B->C)"
ACTION_C_TO_A = "(C->A)"
ACTION_C_TO_B = "(C->B)"


def pour_visited_matrix_dfs():
    # 共六种倒酒情况: A->B, A->C, B->C, B->A, C->A, C->B
    # a, b, c 记录每个状态下的酒的容量
    # 采用 DFS 深度优先遍历的方式，计算所有可能的状态

    # d 是访问数组，d[a][b], a, b 确定后，即可确定 c
    # 初始化为 void
    d = [[ACTION_VOID for _ in range(8)] for _ in range(5)]

    # 起始情况，a=4, b=7
    # 入栈 A, B 容器的现状 和 当前累积的动作
    s = [[4, 7, ACTION_INIT]]
    d[4][4] = ACTION_INIT

    while len(s) > 0:
        # 获取栈顶 a, b
        a, b, actions = s.pop(-1)
        # 推导当前第三个容器的状态
        c = 11 - a - b

        if d[a][b] != ACTION_VOID:
            # 如果访问过，则不再访问
            continue

        d[a][b] = actions
        print(f"{a},{b}=> {actions}")

        # A -> B
        if a > 0 and b < 7:
            x = min(a, 7 - b)
            a1 = a - x
            b1 = b + x
            s.append([a1, b1, actions + ACTION_A_TO_B])
        # A -> C
        if a > 0 and c < 10:
            x = min(a, 10 - c)
            a1 = a - x
            c1 = c + x
            b1 = 11 - a1 - c1
            s.append([a1, b1, actions + ACTION_A_TO_C])
        # B -> A
        if b > 0 and a < 4:
            x = min(b, 4 - a)
            a1 = a + x
            b1 = b - x
            s.append([a1, b1, actions + ACTION_B_TO_A])
        # B -> C
        if b > 0 and c < 10:
            x = min(b, 10 - c)
            c1 = c + x
            b1 = b - x
            a1 = 11 - b1 - c1
            s.append([a1, b1, actions + ACTION_B_TO_C])
        # C -> A
        if c > 0 and a < 4:
            x = min(c, 4 - a)
            a1 = a + x
            c1 = c - x
            b1 = 11 - a1 - c1
            s.append([a1, b1, actions + ACTION_C_TO_A])
        # C -> B
        if c > 0 and b < 7:
            x = min(c, 7 - b)
            b1 = b + x
            c1 = c - x
            a1 = 11 - b1 - c1
            s.append([a1, b1, actions + ACTION_C_TO_B])

    return d


if __name__ == "__main__":
    d = pour_visited_matrix_dfs()

    # 是否存在 (2,x) 和 (x,2) 的情况?
    for a in range(5):
        for b in range(8):
            if (a == 2 or b == 2) and d[a][b] != ACTION_VOID:
                print(f"a={a},b={b}:", d[a][b])
