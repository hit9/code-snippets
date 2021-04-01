// 判断字符串是否是周期串模式
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

    int k = next[n - 1];
    // 如果是周期串，那么 d 就是周期
    // s[k] 是周期串的第一个字符
    int d = k + 1;

    if (d < n && s[k] == s[n - 1] && n % (n - d) == 0) return true;
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
