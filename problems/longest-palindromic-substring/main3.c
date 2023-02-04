// 给出最长回文子串的长度 - 一维动态规划方法
// http://writings.sh/post/algorithm-longest-palindromic-substring

#include <assert.h>  // for assert
#include <stdio.h>   // for printf
#include <string.h>  // for strlen

// 返回给定字符串 s 的最长回文子串的长度
int LongestPalindromicSubstring(char *s) {
    int n = strlen(s);

    if (n <= 0) return 0;

    // dp[j] 表示以位置 j 结尾的最长回文子串的起始位置
    // 其长度就是 j - dp[j] + 1
    int dp[n];
    dp[0] = 0;

    // 记录最大回文子串的长度
    // 0 - 0 + 1
    int max_length = 1;

    for (int j = 1; j < n; j++) {
        if (dp[j - 1] > 0 && s[j] == s[dp[j - 1] - 1]) {
            // 当前位置的字符和上一次回文串的左邻字符相同
            // 回文串得到扩展
            dp[j] = dp[j - 1] - 1;
        } else {
            // 从左向右找
            int left = dp[j - 1];
            int right = j;
            int start = left;  // 最近一次的回文查找起始位置

            while (left < right) {
                if (s[left] != s[right]) {
                    // 遭遇失配字符，重置 right
                    right = j;
                    start = left + 1;
                } else {
                    // 否则，两边继续收拢
                    right--;
                }
                left++;
            }

            dp[j] = start;
        }

        // 更新最大值
        int length = j - dp[j] + 1;
        if (length > max_length) max_length = length;
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
