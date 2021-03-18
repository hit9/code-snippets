// 给出最长回文子串的长度 - 最长公共子串方法
// http://writings.sh/post/algorithm-longest-palindromic-substring

#include <assert.h>  // for assert
#include <stdio.h>   // for printf
#include <string.h>  // for strlen

// 返回字符串 a 和 b 的最长公共子串的长度
// 例如 "abcdbcdef" 和 "bbcbbcdee" 的公共字符串是 "bcde" 长度是 4
int LongestCommonSubstring(char *a, int a_length, char *b, int b_length) {
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
                table[i][j] = 0;
            }

            if (table[i][j] > max) {
                max = table[i][j];
            }
        }
    }

    return max;
}

// 返回给定字符串 s 的最长回文子串的长度
int LongestPalindromicSubstring(char *s) {
    int n = strlen(s);
    char r[n];
    // 反转字符串 s 到 r
    for (int i = 0; i < n; i++) r[i] = s[n - 1 - i];
    return LongestCommonSubstring(s, n, r, n);
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
