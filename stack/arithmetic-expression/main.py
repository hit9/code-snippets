# 四则运算符的优先级，越高值越大
P = {
    "+": 1,
    "-": 1,
    "*": 2,
    "/": 2,
}


# 四则运算
def calc(nums, ops):
    op = ops.pop()
    right = nums.pop()
    left = nums.pop()
    if op == "+":
        nums.append(left + right)
    elif op == "-":
        nums.append(left - right)
    elif op == "*":
        nums.append(left * right)
    elif op == "/":
        nums.append(left // right)


def evaluate(s):
    # 存放待运算的数值，放入一个 0 以防空表达式
    nums = [0]
    # 存放待运算的四则运算符
    # 栈底到栈顶运算符的优先级应该是非降的
    ops = []
    # 将 s 用 () 包裹起来，算作一个规整的表达式
    s = "(" + s + ")"
    i = 0
    while i < len(s):
        x = s[i]
        i += 1
        if x.isspace():  # 忽略空白
            continue
        elif x in P:
            # 当前运算符优先级比如栈顶运算的优先级高
            # 则优先计算栈内
            while ops and ops[-1] in P and P[ops[-1]] >= P[x]:
                calc(nums, ops)
            ops.append(x)
        elif x == "(":
            ops.append(x)
        elif x == ")":
            # 括号包住的表达式，是指不必考虑相邻优先级，优先计算栈内
            while ops and ops[-1] != "(":
                calc(nums, ops)
            ops.pop()  # 弹出左括号
        elif x.isdigit():
            # 向右吸取所有的数字，按十进制取值
            v = int(x)
            while i < len(s) and s[i].isdigit():
                v = v * 10 + int(s[i])
                i += 1
            nums.append(v)
        else:
            raise Exception("bad token")
    return nums.pop()


if __name__ == "__main__":
    assert evaluate("") == 0
    assert evaluate("1") == 1
    assert evaluate("()") == 0
    assert evaluate("(16)") == 16
    assert evaluate("(1+2)*3") == eval("(1+2)*3")
    assert evaluate("1+2*3+4*5") == eval("1+2*3+4*5")
    assert evaluate("5-6*1+2") == 1
    assert evaluate("1+2*3+4*5/3") == eval("1+2*3+4*5//3")
    assert evaluate("1+(2+2)*3 + (3+2)*2+3+3") == eval("1+(2+2)*3 + (3+2)*2+3+3")
    assert evaluate("23 *100 +2 *1+2") == eval("23 *100 +2 *1+2")
    assert evaluate("3+2*3*4+2+1") == eval("3+2*3*4+2+1")
    assert evaluate("2*27-28*2+2+1+6/3") == eval("2*27-28*2+2+1+6//3")
