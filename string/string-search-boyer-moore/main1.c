// Boyer-Moore 字符串匹配算法 (只采用二维坏字符表的方法)
// https://writings.sh/post/algorithm-string-searching-boyer-moore

#include <assert.h>
#include <stdio.h>   // for printf
#include <string.h>  // for strlen, strncmp

// 字符集大小
#define S 256

// ComputeBadCharTable 计算二维坏字符表
void ComputeBadCharTable(char *p, int m, int table[S][m]) {
    // 初始化第一列为 m
    for (int x = 0; x < S; x++) {
        table[x][0] = m;
    }
    // 填表
    for (int x = 0; x < S; x++) {
        for (int k = 1; k < m; k++) {
            if (x == p[k - 1])
                table[x][k] = m - k;
            else  // Copy left
                table[x][k] = table[x][k - 1];
        }
    }
}

// BoyerMoore 从长度为 n 的字符串 s 中查找长度为 m 的字符串 p ， 返回其位置.
// 找不到则返回 -1
// 只采用坏字符表的 BoyerMoore 版本
int BoyerMoore(char *s, int n, char *p, int m) {
    int table[S][m];

    ComputeBadCharTable(p, m, table);

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

        // 失配时，跳转的多少，坏字符表给出跳转量
        i += table[s[i]][j];
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
