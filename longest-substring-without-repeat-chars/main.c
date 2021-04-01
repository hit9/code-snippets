// 无重复字符的最长子串
// https://writings.sh/post/algorithm-longest-substring-without-repeat-chars

#include <assert.h>  // for assert
#include <string.h>  // for strlen

// 动态规划方法

// 返回不包含重复字符的子串的最大长度。
// 例如"abcabcbb" 中不包含重复字符的字符串是 "abc" 其长度是 3
int LongestSubstringWithoutRepeatChars(char *s) {
    int n = strlen(s);
    if (n == 0) return 0;

    // m[ch] 表示字符 ch 最后一次出现的位置，初始化 -1
    int m[256];

    for (int i = 0; i < 256; i++) m[i] = -1;

    // p[i] 记录字符 s[i] 的上一次的出现位置，如果是第一次出现，记 -1
    int p[n];

    for (int i = 0; i < n; i++) {
        char ch = s[i];
        p[i] = m[ch];
        m[ch] = i;
    }

    // dp[i] 表示以位置 i 结尾的最长无重复字符的字符串的长度
    int dp[n];
    dp[0] = 1;

    // 记录 dp[i] 的最大值
    int max_dp = dp[0];

    for (int i = 1; i < n; i++) {
        if (p[i] == -1) {
            // 当前字符第一次出现
            dp[i] = dp[i - 1] + 1;
        } else {
            // 上一个字符串的左边界
            int left_bound = (i - 1) - dp[i - 1];

            if (p[i] < left_bound) {
                // 当前字符上一次出现在 left_bound 之前
                // 说明当前无重复子串的左边界和上一次一样
                // 右边界向右扩展了一位：当前字符，因此长度增 1
                dp[i] = dp[i - 1] + 1;
            } else {
                // 当前字符出现在 left_bound 之后
                // 说明当前无重复子串的左边界是 p[i]
                dp[i] = i - p[i];
            }
        }

        if (dp[i] > max_dp) max_dp = dp[i];
    }

    return max_dp;
}

int main(void) {
    assert(LongestSubstringWithoutRepeatChars("abcabcbb") == 3);
    assert(LongestSubstringWithoutRepeatChars("pwwkew") == 3);
    assert(LongestSubstringWithoutRepeatChars("abcd") == 4);
    assert(LongestSubstringWithoutRepeatChars("abcdababc") == 4);
    return 0;
}
