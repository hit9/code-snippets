// Boyer-Moore 字符串匹配算法
// https://writings.sh/post/algorithm-string-searching-boyer-moore

#include <assert.h>
#include <stdio.h>   // for printf
#include <string.h>  // for strlen, strncmp

// 字符集大小
#define ALPHABET_SIZE 256

#define max(a, b) ((a < b) ? b : a)

// ComputeBadCharTable 计算一维坏字符表
void ComputeBadCharTable(char *p, int m, int table[]) {
    // 初始化每一个字符的坏字符表值为 m
    for (int i = 0; i < ALPHABET_SIZE; i++) {
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

// ComputeGoodSuffixTableCaseNotInLeft
// 填写好后缀表，处理情况：好后缀不在搜索串的左边的情况
void ComputeGoodSuffixTableCaseNotInLeft(char *p, int m, int table[]) {
    int last_prefix_length = 0;

    // 失配位置在 m - 1 时，好后缀无意义，设为跳动最少 1
    table[m - 1] = 1;

    // i 表示后缀的起始位置
    for (int i = m - 1; i > 0; i--) {
        // k 表示失配的位置
        int k = i - 1;
        int suffix_length = m - i;
        char *suffix = p + i;
        int prefix_length = 0;

        if (strncmp(p, suffix, suffix_length) == 0) {
            // 如果后缀是一个前缀
            prefix_length = suffix_length;
            last_prefix_length = prefix_length;
        } else {
            // 否则，沿用上次结果
            prefix_length = last_prefix_length;
        }

        // 计算 d
        table[k] = m + suffix_length - prefix_length;
    }
}

// GetLongestCommonSuffixLength 返回字符串 a 和 b 的最长公共后缀长度。
// 比如 'simple' 和 'example' 的最长公共后缀是 'mple' ，长度是 4.
int GetLongestCommonSuffixLength(char *a, int a_length, char *b, int b_length) {
    int i = 0;
    for (i = 0; i < a_length && i < b_length; i++) {
        if (a[a_length - 1 - i] != b[b_length - 1 - i]) {
            break;
        }
    }
    return i;
}

// ComputeGoodSuffixTableCaseInLeft
// 填写好后缀表，处理情况：好后缀在搜索串的左边的情况
void ComputeGoodSuffixTableCaseInLeft(char *p, int m, int table[]) {
    // e 表示对应的前缀的结尾位置
    for (int e = 0; e < m - 1; e++) {
        // 前缀字符串
        char *prefix = p + e;
        // 前缀的长度
        int prefix_length = e + 1;
        // 最长公共后缀的长度，即好后缀的长度
        int suffix_length =
            GetLongestCommonSuffixLength(p, m, p, prefix_length);

        if (suffix_length > 0) {
            // 好后缀长度 > 0 才有意义
            // t 是重复串的起始位置
            int t = e + 1 - suffix_length;
            // 失配字符的位置
            int k = m - 1 - suffix_length;
            // 填表，覆盖
            table[k] = m - t;
        }
    }
}

// ComputeGoodSuffixTable 计算好后缀表的方法
void ComputeGoodSuffixTable(char *p, int m, int table[]) {
    // 先处理第二种情况：好后缀在搜索串左边不存在的情况
    // 即好后缀和搜索串部分匹配或者完全不匹配的情况
    ComputeGoodSuffixTableCaseNotInLeft(p, m, table);
    // 再处理第一种情况：好后缀在搜索串左边存在的情况
    ComputeGoodSuffixTableCaseInLeft(p, m, table);
}

// BoyerMoore 从长度为 n 的字符串 s 中查找长度为 m 的字符串 p ， 返回其位置.
// 找不到则返回 -1
int BoyerMoore(char *s, int n, char *p, int m) {
    int bad_char_table[ALPHABET_SIZE];
    int good_suffix_table[m];

    ComputeBadCharTable(p, m, bad_char_table);
    ComputeGoodSuffixTable(p, m, good_suffix_table);

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

        // 失配时，跳转的多少，选取坏字符表和好后缀表中最大的跳转量
        i += max(bad_char_table[s[i]], good_suffix_table[j]);
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
