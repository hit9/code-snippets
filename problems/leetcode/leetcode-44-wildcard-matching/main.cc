// https://leetcode.cn/problems/wildcard-matching/description/
// 44. 通配符匹配
// 给你一个输入字符串 (s) 和一个字符模式 (p) ，请你实现一个支持 '?' 和 '*'
// 匹配规则的通配符匹配：
//   '?' 可以匹配任何单个字符。
//   '*' 可以匹配任意字符序列（包括空字符序列）。
// 判定匹配成功的充要条件是：字符模式必须能够 完全匹配
// 输入字符串（而不是部分匹配）。
//
// 示例 1： 输入：s = "aa", p = "a" 输出：false 解释："a" 无法匹配 "aa"
// 整个字符串。
//
// 示例 2： 输入：s = "aa", p = "*" 输出：true 解释：'*' 可以匹配任意字符串。
//
// 示例 3： 输入：s = "cb", p = "?a" 输出：false 解释：'?' 可以匹配 'c',
// 但第二个 'a' 无法匹配 'b'。
//
// 0 <= s.length, p.length <= 2000
// s 仅由小写英文字母组成
// p 仅由小写英文字母、'?' 或 '*' 组成

#include <string>
using namespace std;
class Solution {
   public:
    bool isMatch(string s, string p) {
        // 预处理
        s.insert(s.begin(), '^');
        p.insert(p.begin(), '^');

        auto m = p.size();
        auto n = s.size();

        // dp[i][j] 表示 s[:j] 是否匹配 p[:i]
        int dp[m][n];
        for (auto i = 0; i < m; i++)
            for (auto j = 0; j < n; j++) dp[i][j] = false;
        dp[0][0] = true;

        for (auto i = 1; i < m; i++) {
            int k = n;  // 用于寻找上一行的最早匹配点
            switch (p[i]) {
                case '*':
                    for (auto j = 0; j < n; j++) {
                        if (dp[i - 1][j]) {
                            k = j;
                            break;
                        }
                    }
                    for (auto j = k; j < n; j++) dp[i][j] = true;
                    break;
                case '?':
                    for (auto j = 1; j < n; j++)
                        if (dp[i - 1][j - 1]) dp[i][j] = true;
                    break;
                default:
                    for (auto j = 1; j < n; j++)
                        if (dp[i - 1][j - 1] && s[j] == p[i]) dp[i][j] = true;
            }
        }

        return dp[m - 1][n - 1];
    }
};

int main(void) { return 0; }
