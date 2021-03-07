// 最长公共子序列
// https://writings.sh/post/algorithm-longest-common-substring-and-longest-common-subsequence

#include <assert.h>
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

int main(void) {
    char *a1 = "abcbcde";
    char *b1 = "acabdef";
    assert(LongestCommonSubsequence(a1, strlen(a1), b1, strlen(b1)) == 5);
}
