// Boyer-Moore 字符串匹配算法 - 只采用一维坏字符表
// https://writings.sh/post/algorithm-string-searching-boyer-moore

#include <assert.h>
#include <stdio.h>   // for printf
#include <string.h>  // for strlen, strncmp

// 字符集大小
#define S 256

#define max(a, b) ((a < b) ? b : a)

// ComputeBadCharTable 计算一维坏字符表
void ComputeBadCharTable(char *p, int m, int table[]) {
    // 初始化每一个字符的坏字符表值为 m
    for (int i = 0; i < S; i++) {
        table[i] = m;
    }
    // 对尾巴左边的字符，不断覆盖它到尾巴 last 的距离
    // 此处采用 i < last 而非 i <= last 是因为尾巴字符到本身的距离是 0
    // 坏字符的对齐目标绝不在尾巴字符上。
    int last = m - 1;
    for (int i = 0; i < last; i++) {
        char ch = p[i];
        table[ch] = last - i;
    }
}

// BoyerMoore 从长度为 n 的字符串 s 中查找长度为 m 的字符串 p ， 返回其位置.
// 找不到则返回 -1
// 只采用一维坏字符表的方式
int BoyerMoore(char *s, int n, char *p, int m) {
    int bad_char_table[S];

    ComputeBadCharTable(p, m, bad_char_table);

    // 初始化，i, j 右对齐
    int i = m - 1;

    while (i < n) {
        int j = m - 1;

        // 自右向左匹配
        while (j >= 0 && p[j] == s[i]) {
            j--;
            i--;
        }

        if (j < 0) {
            // 命中, 返回起始位置
            return i + 1;
        }

        // 失配时，跳转的多少
        // 如果只是采用 i = bad_char_table[s[i]] 的话，会有可能发生匹配回溯
        // 我们要至少子串右移对齐一位，即主串迭代至少 m-j 才行
        i += max(bad_char_table[s[i]], m - j);
    }

    return -1;
}

int main(void) {
    char *s = "ABCDABEABDCBCDDBBCDBACD";
    char *p1 = "BCDBACD";
    char *p2 = "BCDDBB";
    char *p3 = "EABDCB";
    char *p4 = "BBCDBD";
    char *p5 = "DDBBCD";

    char *s1 = "BBBBBBBBBBBBBBBBBBBBBABBBBB";
    char *p6 = "ABBBBB";

    assert(BoyerMoore(s, strlen(s), p1, strlen(p1)) == 16);
    assert(BoyerMoore(s, strlen(s), p2, strlen(p2)) == 11);
    assert(BoyerMoore(s, strlen(s), p3, strlen(p2)) == 6);
    assert(BoyerMoore(s, strlen(s), p4, strlen(p4)) == -1);
    assert(BoyerMoore(s, strlen(s), p5, strlen(p5)) == 13);
    assert(BoyerMoore(s1, strlen(s1), p6, strlen(p6)) == 21);
    return 0;
}
