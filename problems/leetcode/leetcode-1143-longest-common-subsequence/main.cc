// LCS 最长公共子序列问题
// https://leetcode.cn/problems/longest-common-subsequence

#include <string>
#include <vector>
using namespace std;
class Solution {
   public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();

        // dp[i][j] 表示以 text1[0..i-1] 和 text2[0..j-1]
        // 两个子串的最长公共子序列的长度
        // 故意多加了一行和一列，以简化边界处理
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (text1[i] == text2[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                } else {
                    dp[i + 1][j + 1] = std::max(dp[i][j + 1], dp[i + 1][j]);
                }
            }
        }

        return dp[m][n];
    }
};
