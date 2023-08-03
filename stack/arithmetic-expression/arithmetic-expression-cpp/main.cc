// 双栈法 算术表达式求值 - C++ 版本
// 支持多位整数
// 博客 - 算术表达式求值（双栈法）
// https://writings.sh/post/arithmetic-expression

#include <ctype.h>

#include <cassert>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

// 四则运算符的优先级，越高值越大
const std::unordered_map<char, int> P = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
};

// 四则运算
void calc(std::stack<int>& nums, std::stack<char>& ops) {
    if (ops.empty()) return;

    auto op = ops.top();
    auto right = nums.top();
    nums.pop();
    auto left = nums.top();
    nums.pop();

    switch (op) {
        case '+':
            nums.push(left + right);
            break;
        case '-':
            nums.push(left - right);
            break;
        case '*':
            nums.push(left * right);
            break;
        case '/':
            nums.push(left / right);
            break;
    }
    ops.pop();
}

int to_int(char ch) { return ch - '0'; }

int evaluate(const std::string& s) {
    // 存放待运算的数值，放入一个 0 以防空表达式
    std::stack<int> nums;
    // 存放待运算的四则运算符
    // 栈底到栈顶运算符的优先级应该是非降的
    std::stack<char> ops;

    nums.push(0);

    int i = 0;
    while (i < s.length()) {
        char x = s[i++];

        if (isdigit(x)) {
            // 向右吸取所有的数字，按十进制取值
            int v = to_int(x);
            while (i < s.length() && isdigit(s[i])) {
                v = v * 10 + to_int(s[i]);
                i++;
            }
            nums.push(v);
        } else if (P.contains(x)) {
            // 当前运算符优先级比如栈顶运算的优先级高
            // 则优先计算栈内
            while (!ops.empty() && P.contains(ops.top()) &&
                   P.at(ops.top()) >= P.at(x)) {
                calc(nums, ops);
            }
            ops.push(x);
        } else if (x == '(') {
            ops.push(x);
        } else if (x == ')') {
            // 括号包住的表达式，是指不必考虑相邻优先级，优先计算栈内
            while (!ops.empty() && ops.top() != '(') {
                calc(nums, ops);
            };
            ops.pop();  // 弹出左括号
        }
    }
    // 把栈内剩余运算执行完
    while (!ops.empty()) calc(nums, ops);
    return nums.top();
}

// 测试
int main(void) {
    assert(evaluate("") == 0);
    assert(evaluate("1") == 1);
    assert(evaluate("()") == 0);
    assert(evaluate("(16)") == 16);
    assert(evaluate("(1+2)*3") == (1 + 2) * 3);
    assert(evaluate("1+2*3+4*5") == (1 + 2 * 3 + 4 * 5));
    assert(evaluate("5-6*1+2") == 1);
    assert(evaluate("1+2*3+4*5/3") == (1 + 2 * 3 + 4 * 5 / 3));
    assert(evaluate("1+(2+2)*3 + (3+2)*2+3+3") ==
           1 + (2 + 2) * 3 + (3 + 2) * 2 + 3 + 3);
    assert(evaluate("23 *100 +2 *1+2") == 23 * 100 + 2 * 1 + 2);
    assert(evaluate("3+2*3*4+2+1") == 3 + 2 * 3 * 4 + 2 + 1);
    assert(evaluate("2*27-28*2+2+1+6/3") == 2 * 27 - 28 * 2 + 2 + 1 + 6 / 3);
    return 0;
}
