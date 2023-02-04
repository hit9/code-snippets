// 最长公共子串 - 动态规划方法
// https://writings.sh/post/algorithm-longest-common-substring-and-subsequence

#include <assert.h>
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

int main(void) {
    char *a1 = "abcdbcdef";
    char *b1 = "bbcbbcdee";
    assert(LongestCommonSubstring(a1, strlen(a1), b1, strlen(b1)) == 4);

    char *a2 = "fish";
    char *b2 = "fosh";
    assert(LongestCommonSubstring(a2, strlen(a2), b2, strlen(b2)) == 2);

    char *a3 = "abcbcdefg";
    char *b3 = "gbcbcde";
    assert(LongestCommonSubstring(a3, strlen(a3), b3, strlen(b3)) == 6);

    char *a4 = "abcbcde";
    char *b4 = "bbcbce";
    assert(LongestCommonSubstring(a4, strlen(a4), b4, strlen(b4)) == 4);

    char *a5 = "abc";
    char *b5 = "aef";
    assert(LongestCommonSubstring(a5, strlen(a5), b5, strlen(b5)) == 1);
}
