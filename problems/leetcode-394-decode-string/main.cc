// https://leetcode.cn/problems/decode-string/description/?envType=study-plan-v2&envId=top-100-liked
// 给定一个经过编码的字符串，返回它解码后的字符串。
// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k
// 次。注意 k 保证为正整数。
// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k
// ，例如不会出现像 3a 或 2[4] 的输入。
// 示例 1： 输入：s = "3[a]2[bc]" 输出："aaabcbc"
// 示例 2： 输入：s = "3[a2[c]]" 输出："accaccacc"
// 示例 3： 输入：s = "2[abc]3[cd]ef" 输出："abcabccdcdcdef"
// 示例 4： 输入：s = "abc3[cd]xyz" 输出："abccdcdcdxyz"
// 保证是一个 有效 的输入。
// s 中所有整数的取值范围为 [1, 300]

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isnum(char ch) { return ch >= '0' && ch <= '9'; }

class Solution {
   public:
    string decodeString(string s) {
        stack<int> sk;
        stack<string> ss;

        ss.push("");

        int k = 0;  // 解析中的数字

        for (auto ch : s) {
            if (isnum(ch)) {
                // 数字栈顶, 数字更新
                k = (ch - '0') + 10 * k;
            } else {
                switch (ch) {
                    case '[':
                        // 新建空串入栈
                        ss.push("");
                        // k 入栈
                        sk.push(k);
                        k = 0;
                        break;
                    case ']': {
                        // 出栈计算
                        auto k1 = sk.top();
                        auto s1 = ss.top();
                        sk.pop();
                        ss.pop();

                        // 重复字符串后，连接到栈顶
                        for (auto i = 0; i < k1; i++) ss.top() += s1;
                    } break;
                    default:
                        // 字母, 连接到栈顶的字符串
                        ss.top().push_back(ch);
                }
            }
        }

        return ss.top();
    }
};

int main(void) {
    Solution solution;
    cout << solution.decodeString("ab3[a2[c]de10[k]]fg") << endl;
    return 0;
}
