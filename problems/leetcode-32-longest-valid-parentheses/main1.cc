#include <string>

using namespace std;

// dp 的做法
// dp[i] = dp[i-1] + 2 + dp[i-1 - dp[i-1] - 1]
// dp[i] 的含义是以第 i 个字符为尾巴的最长有效字符串的长度
// 当 s[i] 为 ')' 时，和左边的比较 '(' 则扩展

class Solution {
   public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> dp(n, 0);

        int m = 0;

        for (int i = 1; i < s.size(); i++) {
            if (s[i] == ')') {
                int j = i - 1 - dp[i - 1];
                if (j >= 0 && s[j] == '(') {
                    dp[i] = 2 + dp[i - 1];
                    if (j >= 1) dp[i] += dp[j - 1];
                }
            }
            m = std::max(dp[i], m);
        }
        return m;
    }
};
