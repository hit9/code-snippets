// 给出最长回文子序列 - 反转 + 最长公共子序列方法
// http://writings.sh/post/algorithm-longest-palindromic-subsequence

#include <assert.h>  // for assert
#include <stdio.h>   // for printf
#include <string.h>  // for strlen

#define MAX(a, b) (a) > (b) ? (a) : (b)

// 返回两个字符串 a 和 b 的最长公共子序列的长度
// 例如 "abcbcde" 和 "acabdef" 的最长公共子序列是 "acbde" ，长度为 5
int LongestCommonSubsequence(char *a, int a_length, char *b, int b_length) {
    int table[a_length][b_length];
    int max = 0;

    for (int i = 0; i < a_length; i++) {
        for (int j = 0; j < b_length; j++) {
            if (a[i] == b[j]) {
                if (i >= 1 && j >= 1)
                    table[i][j] = table[i - 1][j - 1] + 1;
                else
                    table[i][j] = 1;
            } else {
                if (i >= 1 && j >= 1)
                    table[i][j] = MAX(table[i - 1][j], table[i][j - 1]);
                else if (i <= 0 && j >= 1)
                    table[i][j] = table[i][j - 1];
                else if (i >= 1 && j <= 0)
                    table[i][j] = table[i - 1][j];
                else
                    table[i][j] = 0;
            }

            if (max < table[i][j]) max = table[i][j];
        }
    }
    return max;
}

// 返回给定字符串 s 的最长公共子序列的长度
int LongestPalindromicSubsequence(char *s) {
    int n = strlen(s);
    if (n <= 0) return 0;
    char r[n];
    for (int i = 0; i < n; i++) r[i] = s[n - 1 - i];
    return LongestCommonSubsequence(s, n, r, n);
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
