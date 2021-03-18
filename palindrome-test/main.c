// 回文串判断
// https://writings.sh/post/algorithm-longest-palindromic-substring

#include <assert.h>
#include <stdbool.h>  // for bool
#include <string.h>   // for strlen

// 判断给定字符串是否是回文串
bool IsPalindromicString(char *s) {
    int n = strlen(s);
    int left = 0;
    int right = n - 1;

    while (left < right) {
        if (s[left] == s[right]) {
            left++;
            right--;
        } else {
            return false;
        }
    }
    return true;
}

int main(void) {
    assert(IsPalindromicString("abcba"));
    assert(IsPalindromicString("abccba"));
    assert(IsPalindromicString("aa"));
    assert(IsPalindromicString("a"));
    assert(!IsPalindromicString("a123"));
    assert(!IsPalindromicString("ab"));
    assert(IsPalindromicString(""));
    return 0;
}
