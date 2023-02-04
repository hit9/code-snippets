// 给出最长回文子串的长度 - Manacher 方法
// http://writings.sh/post/algorithm-longest-palindromic-substring

#include <assert.h>  // for assert
#include <stdio.h>   // for printf
#include <string.h>  // for strlen

// 预处理过程，n 是原字符串 s 的长度
// 预期结果 s1 的长度是 2n + 1
// 例如 "aba" => "|a|b|a|"
void ManacherPreprocess(char *s, int n, char *s1) {
    int i = 0;
    int j = 0;
    while (i < n) {
        s1[j++] = '|';
        s1[j++] = s[i++];
    }
    // 末尾补 '|'
    s1[j++] = '|';
}

#define min(x, y) (x) < (y) ? (x) : (y)

// Manacher 算法主过程
// 输入长度为奇数的已预处理过的字符串 s 和其长度 n
// 返回最长回文串的半径
int Manacher(char *s, int n) {
    // 最长回文串半径的数组
    int p[n];
    // 显然 第一位的半径是 0
    p[0] = 0;
    // 追踪数组 p 的最大值
    int max_p = 0;

    // 维护向右延伸最远的回文串的信息
    // 其最右的位置 r
    int r = 0;
    // 其中心位置 c
    int c = 0;

    // 求解数组 p
    for (int i = 1; i < n; i++) {
        // 找出 i 为中心的回文串半径 p[i]
        if (i < r) {
            // 目标回文串的中心在 r 左边时
            // 最大化吸收已有信息

            // j 是 i 关于 c 对称的位置
            int j = c - (i - c);

            // p[i] 至少为下面二者最小值
            p[i] = min(p[j], r - i);
        } else {
            // 否则，初始化 p[i]
            p[i] = 0;
        }

        int left = i - p[i] - 1;
        int right = i + p[i] + 1;

        while (s[left] == s[right] && left >= 0 && right < n) {
            left--;
            right++;
            p[i]++;
        }

        // 真实的 right
        right = i + p[i];

        // 维护 c 和 r
        if (right > r) {
            r = right;
            c = i;
        }

        // 维护最大值
        if (max_p < p[i]) max_p = p[i];
    }
    return max_p;
}

// 返回给定字符串 s 的最长回文子串的长度
int LongestPalindromicSubstring(char *s) {
    int n = strlen(s);
    if (n <= 0) return 0;

    // 预处理
    int n1 = 2 * n + 1;
    char s1[n1];
    ManacherPreprocess(s, n, s1);

    // s1 的回文半径 就是 s 的回文长度
    return Manacher(s1, n1);
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
