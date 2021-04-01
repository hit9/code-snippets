// 判断字符串是否是周期串模式
// https://writings.sh/post/algorithm-repeated-string-pattern
// 双倍字符串方法

#include <assert.h>
#include <stdbool.h>  // for bool
#include <string.h>   // for strlen, strstr, strcpy

// 判断 s 是否是周期串模式
// 比如 abcabcabc => true
// 比如 abcabcabd => false
bool IsStringRepeatedPattern(char *s) {
    int n = strlen(s);

    if (n <= 0) return 0;

    char a[2 * n - 2];  // s[1:] + s[:n-1]

    strcpy(a, s + 1);              // 拷贝 s[1:]
    strncpy(a + n - 1, s, n - 1);  // 拷贝 s[:n-1]

    if (strstr(a, s) != NULL) return true;
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
