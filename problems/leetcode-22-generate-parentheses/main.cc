// https://leetcode.cn/problems/generate-parentheses/description/?envType=study-plan-v2&envId=top-100-liked
// 22. 括号生成
// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且
// 有效的 括号组合。 输入：n = 3
// 输出：["((()))","(()())","(())()","()(())","()()()"]

// 思路 DP
// 递推公式. 任何长度为 i 的括号字符串可以写成形式:  ( left ) right
//  其中 left: 0~j, right 0~i-j-1

#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string>> dp(n + 1);
        if (n >= 0) dp[0].push_back("");
        if (n >= 1) dp[1].push_back("()");

        for (auto i = 2; i <= n; i++) {
            for (auto j = 0; j < i; j++) {
                for (auto left : dp[j]) {
                    for (auto right : dp[i - j - 1])
                        dp[i].push_back("(" + left + ")" + right);
                }
            }
        }
        return dp[n];
    }
};
