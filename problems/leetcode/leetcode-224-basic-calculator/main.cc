#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isdigit(char ch) { return ch >= '0' && ch <= '9'; }
int char2digit(char ch) { return ch - '0'; }

class Solution {
   public:
    void reduce(stack<char>& ops, stack<int>& nums) {
        auto op = ops.top();
        ops.pop();
        switch (op) {
            int b;
            int a;
            case '+':
                b = nums.top();
                nums.pop();
                a = nums.top();
                nums.pop();
                nums.push(a + b);
                break;
            case '-':
                b = nums.top();
                nums.pop();
                a = nums.top();
                nums.pop();
                nums.push(a - b);
                break;
        }
    }

    int calculate(string s) {
        stack<char> ops;
        stack<int> nums;

        int n = s.size();

        int k = 0;  // 当前正在解析的整数
        char b = '\0';  // 记录上一个 token 的类型, 数字是 '0', 空格忽略

        for (int i = 0; i < n; i++) {
            char ch = s[i];

            switch (ch) {
                case ' ':
                    continue;  // 忽略空白
                case '-':
                    // 要区分是否是一元操作符, 一元的话，添加一个 0 转化到 2 元
                    // 一元负号左边一个 token 是 (  或者无 token
                    if (b == '\0' || b == '(' || nums.empty()) nums.push(0);
                    [[fallthrough]];
                case '+':
                    // push 前先计算栈顶数据, 目前没有优先级的概念, 可以直接计算
                    while (!ops.empty() &&
                           (ops.top() == '+' || ops.top() == '-'))
                        reduce(ops, nums);
                    ops.push(ch);
                    b = ch;
                    break;
                case '(':  //  直接 push
                    ops.push(ch);
                    b = ch;
                    break;
                case ')':
                    // 执行计算
                    while (!ops.empty() && ops.top() != '(') reduce(ops, nums);
                    ops.pop();  // 弹出左括号
                    b = ch;
                    break;
                default:
                    if (isdigit(ch)) {
                        // 数字
                        k = k * 10 + char2digit(ch);

                        // 数字结束输入时, 把数字收纳到栈中
                        if (i == n - 1 || !isdigit(s[i + 1])) {
                            nums.push(k);
                            k = 0;
                            b = '0';
                        }
                    }
                    break;
            }
        }

        // 计算完剩余的部分
        while (!ops.empty()) reduce(ops, nums);
        return nums.top();
    }
};

int main(void) {
    Solution solution;
    //    cout << solution.calculate("-5") << endl;
    //    cout << solution.calculate("-(-5)") << endl;
    //    cout << solution.calculate("1+((3-2)+(-2))") << endl;
    cout << solution.calculate(" 2-1 + 2 ") << endl;
    return 0;
}
