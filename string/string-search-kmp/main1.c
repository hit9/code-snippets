// 字符串搜索 KMP 算法
// https://writings.sh/post/algorithm-string-searching-kmp

#include <assert.h>
#include <stdio.h>   // for printf
#include <string.h>  // for strlen

// 简化的 ComputeNext 方法

// ComputeNext 为长度为 m 的搜索串 p 计算 next 数组.
// next 数组的含义：
// 取字符串 p 的位置 j 之前的前缀字符串 p'，其头尾的最大公共长度即 next[j].
// 在 KMP 中，next 数组的值的应用为，在 j 处失配时的跳转位置是 next[j].
// 此处采用归纳方法实现
void ComputeNext(char *p, int m, int next[]) {
    if (m > 0) next[0] = 0;
    if (m > 1) next[1] = 0;

    for (int j = 2; j < m; j++) {
        char ch = p[j - 1];
        int k = next[j - 1];
        // 向前跳跃匹配前缀
        while (k != 0 && ch != p[k]) k = next[k];
        next[j] = 0;  // 找不到默认为 0
        // 找到了，长度是 匹配位置 + 1
        if (ch == p[k]) next[j] = k + 1;
    }
}

// KMP 从长度为 n 的字符串 s 中查找长度为 m 的字符串 p ，返回其位置.
// 找不到则返回 -1
int KMP(char *s, int n, char *p, int m) {
    // 预处理 next 数组
    int next[m];
    ComputeNext(p, m, next);

    // i 遍历 s
    // j 遍历 p
    int i = 0;
    int j = 0;

    while (i < n) {
        // 匹配
        if (s[i] == p[j]) {
            if (j == m - 1) {
                // 子串匹配到尾部，说明命中
                // 返回匹配的起始位置
                return i + 1 - m;
            } else {
                // 否则，则继续匹配
                i++;
                j++;
            }
        } else {
            if (j == 0) {
                // j 已经在串首, 说明第一个字符不匹配
                // 不必再回溯子串，主串迭代进 1
                i++;
            } else {
                // 失配，j 回溯
                // 回溯的目标位置，已经匹配到的子串的头尾公共部分的长度处
                j = next[j];
            }
        }
    }

    return -1;  // 查找失败
}

int main(void) {
    char *s = "ABCDABCABCABABCABCDA";
    char *p = "ABCABCD";
    char *p1 = "ABCABCF";
    char *p2 = "ABCDA";
    char *p3 = "BABC";

    char *s1 = "aabaaabaaac";
    char *p4 = "aabaaac";

    assert(KMP(s, strlen(s), p, strlen(p)) == 12);
    assert(KMP(s, strlen(s), p1, strlen(p1)) == -1);
    assert(KMP(s, strlen(s), p2, strlen(p2)) == 0);
    assert(KMP(s, strlen(s), p3, strlen(p3)) == 11);
    assert(KMP(s1, strlen(s1), p4, strlen(p4)) == 4);
    return 0;
}
