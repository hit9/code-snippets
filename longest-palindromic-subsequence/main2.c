// 给出最长回文子序列 - 动态规划方法
// http://writings.sh/post/algorithm-longest-palindromic-subsequence

#include <assert.h>  // for assert
#include <stdio.h>   // for printf
#include <string.h>  // for strlen

#define max(a, b) (a) > (b) ? (a) : (b)

// 返回给定字符串 s 的最长公共子序列的长度
int LongestPalindromicSubsequence(char *s) {
    int n = strlen(s);
    if (n <= 0) return 0;

    // dp[i][j] 表示子串 i..j 内的最长回文序列长度
    int dp[n][n];

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            // 初始化，至少为 1
            dp[i][j] = 1;
            if (s[i] == s[j]) {
                // 第一种情况，两边字符相等 回文序列长度 += 2
                // 注意子串i+1..j-1 的有效性
                if (i + 1 <= j - 1)
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else {
                    // 即 j-i <= 1 ，此时 i..j 至多有 2 个字符
                    // 两个字符相等时，自身回文，取其长度
                    dp[i][j] = j - i + 1;
                }
            } else {
                // 第一种情况，两边字符不等 回文序列长度取左右之大
                // 此时必然 j > i
                // 所以，一定有 j >= i+1  或者 i-1 <= j，也就是子串一定有效
                // 仍需要注意 i+1 和 j-1 的越界处理
                if (i + 1 < n) dp[i][j] = max(dp[i][j], dp[i + 1][j]);
                if (j - 1 >= 0) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][n - 1];
}

int main(void) {
    assert(LongestPalindromicSubsequence("aba") == 3);
    assert(LongestPalindromicSubsequence("ababbdab") == 6);
    assert(LongestPalindromicSubsequence("abcabcabc") == 5);
    assert(LongestPalindromicSubsequence("abbcbb") == 5);
    assert(LongestPalindromicSubsequence("bbab") == 3);
    assert(LongestPalindromicSubsequence("") == 0);
    assert(LongestPalindromicSubsequence("abaabababababbabba") == 15);
    return 0;
}
