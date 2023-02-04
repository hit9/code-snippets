// 给出最长回文子串的长度 - 中心扩展法
// http://writings.sh/post/algorithm-longest-palindromic-substring

#include <assert.h>  // for assert
#include <stdio.h>   // for printf
#include <string.h>  // for strlen

// 辅助函数：从长度为 n 的字符串 s 的给定位置左右扩展寻找回文串。
// 输入的 left 和 right 是扩展的左右起始位置。
// 返回扩展经过的字符数 k .
int ExpandPalindrome(char *s, int n, int left, int right) {
    int k = 0;
    while (left >= 0 && right < n) {
        if (s[left] == s[right]) {
            left--;
            right++;
            k++;
        } else {
            break;
        }
    }
    return k;
}

// 返回给定字符串 s 的最长回文子串的长度
int LongestPalindromicSubstring(char *s) {
    int n = strlen(s);

    if (n <= 0) return 0;

    // 记录最大回文子串的长度
    // 一旦 s 非空，必然最大回文子串长度至少为 1
    int max_length = 1;

    for (int i = 0; i < n; i++) {
        // 考察回文串长度是奇数的情况
        int k1 = ExpandPalindrome(s, n, i - 1, i + 1);
        // 考察回文串长度是偶数的情况
        int k2 = ExpandPalindrome(s, n, i, i + 1);

        // 计算两个情况下的长度
        int length1 = k1 * 2 + 1;
        int length2 = k2 * 2;

        // 更新最大值
        if (length1 > max_length) max_length = length1;
        if (length2 > max_length) max_length = length2;
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
