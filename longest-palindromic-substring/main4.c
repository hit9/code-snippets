// 给出最长回文子串的长度 - 二维动态规划方法
// http://writings.sh/post/algorithm-longest-palindromic-substring

#include <assert.h>   // for assert
#include <stdbool.h>  // for bool
#include <stdio.h>    // for printf
#include <string.h>   // for strlen

// 返回给定字符串 s 的最长回文子串的长度
int LongestPalindromicSubstring(char *s) {
    int n = strlen(s);

    if (n <= 0) return 0;

    // dp[i][j] 表示 s[i..j] 是否回文，j >= i
    bool dp[n][n];

    // 初始化
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) dp[i][j] = false;

    // 易知，单个字符 s[i..i] 构成回文
    for (int i = 0; i < n; i++) dp[i][i] = true;

    // 记录最大回文子串的长度，至少为 1
    int max_length = 1;

    // 考虑递推
    // 主要的递推关系是 dp[i][j] = dp[i+1][j-1]
    // 所以倒序遍历 i ，才可以形成递推
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            if (s[i] == s[j]) {
                if (j - 1 >= i + 1) {  // 子串 s[i+1][j-1] 有效性
                    if (dp[i + 1][j - 1]) dp[i][j] = true;
                } else {
                    // 此时 j < i + 2 即 j <= i+1 ，再之 s[i] == s[j]，必回文
                    dp[i][j] = true;
                }
            }

            if (dp[i][j]) {
                // 更新最大长度
                int length = j - i + 1;
                if (length > max_length) max_length = length;
            }
        }
    }
    return max_length;
}

int main(void) {
    assert(LongestPalindromicSubstring("aba") == 3);
    assert(LongestPalindromicSubstring("xabay") == 3);
    assert(LongestPalindromicSubstring("ababababab") == 9);
    assert(LongestPalindromicSubstring("a") == 1);
    assert(LongestPalindromicSubstring("") == 0);
    assert(LongestPalindromicSubstring("aabbab") == 4);
    return 0;
}
