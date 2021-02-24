// 字符串搜索 KMP 算法
// https://writings.sh/post/algorithm-string-searching-kmp

#include <stdio.h>  // for printf

// ComputeNext 为长度为 m 的模式串 p 计算 next 数组.
// next 数组的含义：
// 取字符串 p 的位置 j 之前的前缀字符串 p' ，其头尾的最大公共长度即 next[j]
// 此处采用递推方法实现
void ComputeNext(char *p, int m, int next[]) {
    next[0] = 0;
    if (m <= 1) return;

    // p' 是单个字符时，认为它无公共头尾
    next[1] = 0;

    // j 是 next 数组的第 j 项
    // p' 是字符串 p 的长度为 j 的子串
    int j = 2;

    while (j < m) {
        if (p[j - 1] == p[next[j - 1]]) {
            next[j] = next[j - 1] + 1;
        } else {
            next[j] = 0;
        }

        j++;
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
    char *s = "ABCDABCABCABABCABCDA";  // length => 20
    char *p = "ABCABCD";               // length => 7
    char *t = "ABCABCF";               // length => 7

    int pos_of_p = KMP(s, 20, p, 7);
    int pos_of_t = KMP(s, 20, t, 7);

    printf("position of p in s: %d\n", pos_of_p);  // Expect: 12
    printf("position of t in s: %d\n", pos_of_t);  // Expect: -1
}
