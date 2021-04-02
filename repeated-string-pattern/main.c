// 判断字符串是否是周期串模式
// https://writings.sh/post/algorithm-repeated-string-pattern
// 采用 KMP Next 数组的方法

#include <assert.h>
#include <stdbool.h>  // for bool
#include <string.h>   // for strlen

// 同 KMP 的 Next 数组
// https://writings.sh/post/algorithm-string-searching-kmp
void ComputeNext(char *s, int n, int next[]) {
    if (n > 0) next[0] = 0;
    if (n > 1) next[1] = 0;

    for (int j = 2; j < n; j++) {
        char ch = s[j - 1];
        int k = next[j - 1];

        while (k != 0 && s[k] != ch) k = next[k];

        next[j] = 0;
        if (s[k] == ch) next[j] = k + 1;
    }
}

// 判断 s 是否是周期串模式
// 比如 abcabcabc => true
// 比如 abcabcabd => false
bool IsStringRepeatedPattern(char *s) {
    int n = strlen(s);
    if (n == 0) return false;

    int next[n];
    ComputeNext(s, n, next);

    // s[0:n-1] 的最长的前后公共缀长度
    int c = next[n - 1];
    // 预期的周期长度
    int d = (n - 1) - c;

    if (d > 0 && s[c] == s[n - 1] && n % d == 0) return true;
    return false;
}

int main(void) {
    assert(IsStringRepeatedPattern("abcabc"));
    assert(IsStringRepeatedPattern("abcabcabc"));
    assert(IsStringRepeatedPattern("abaccbabaccbabaccb"));
    assert(!IsStringRepeatedPattern("abababa"));
    assert(IsStringRepeatedPattern("ababab"));
    assert(!IsStringRepeatedPattern("ab"));
    assert(!IsStringRepeatedPattern("a"));
    assert(IsStringRepeatedPattern("aa"));
    assert(IsStringRepeatedPattern("bbabbabba"));
    return 0;
}
