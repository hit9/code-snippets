// https://leetcode.cn/problems/minimum-insertions-to-balance-a-parentheses-string
// 1541. 平衡括号字符串的最少插入次数

#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
   public:
    int minInsertions(string s) {
        stack<char> a;

        int ans = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == ')') {
                if (!a.empty() && a.top() == ')') {
                    a.pop();
                    a.push('x');
                } else {
                    a.push(')');
                }
            } else {  // '('
                if (!a.empty() && a.top() == ')') {
                    // 栈内是奇数个 _，要插入一个 )
                    // 也就是换成 x
                    a.pop();
                    a.push('x');
                    ans++;
                }
                // 每遇到一个左括号，都需要 1个 x 来平衡
                if (a.size() == 0) {
                    // 需要两个 )
                    ans += 2;
                } else {
                    a.pop();  // 弹出 x
                }
            }
        }

        // 栈顶如果是 )
        // 则 push 一个 ), 变成 x
        if (!a.empty() && a.top() == ')') {
            // 栈内是奇数个 )，要插入一个 )
            // 也就是换成 x
            a.pop();
            a.push('x');
            ans++;
        }

        if (!a.empty()) {
            // 栈内剩余的 x, 也需要左括号来平衡
            ans += a.size();
        }
        return ans;
    }
};

int main(void) {
    Solution solution;

    cout << solution.minInsertions(
                "))(()()))()))))))()())()(())()))))()())(()())))()(")
         << endl;
    return 0;
}
