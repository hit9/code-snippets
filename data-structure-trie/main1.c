// 字典树
// https://zh.wikipedia.org/zh-hans/Trie

// 基于数组的基本实现
// 假设字符集 a-z 共 26 个字符，最多 MAXN 个节点

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 10010  // 最大节点数

// 字典树 - 数组实现
typedef struct {
    // a[j] 表示第 j 个节点
    // a[j][k] 表示它的第 k 个孩子，代表字符 k+'a'
    // a[j][k] -> j' 表示下一个节点是 j' , -1 表示无存储
    int a[MAXN][26];
    int n;  // 节点数目
    // end[j] 表示第 j 个节点是否是某个单词的末尾
    bool end[MAXN];
} Trie;

void Init(Trie *t) {
    if (t == NULL) return;

    t->n = 0;

    for (int j = 0; j < MAXN; j++) {
        for (int k = 0; k < 26; k++) {
            // a[j][k] 为 -1 表示此位置无字符存储
            t->a[j][k] = -1;
        }
        t->end[j] = false;
    }
}

// 添加字符串
void Put(Trie *t, char *s) {
    if (t == NULL) return;

    int j = 0;  // 当前迭代节点

    for (int i = 0; s[i] != '\0'; i++) {
        int k = s[i] - 'a';

        if (t->a[j][k] == -1) {
            // 当前位置无存储，标记已存储
            t->n++;
            t->a[j][k] = t->n;  // 指向下一节点
        }

        j = t->a[j][k];
    }

    t->end[j] = true;
}

// 前缀匹配，返回最后一个节点索引
// 如果未匹配，返回 -1
int Match(Trie *t, char *s) {
    if (t == NULL) return false;

    int j = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        int k = s[i] - 'a';
        if (t->a[j][k] == -1) return -1;
        j = t->a[j][k];
    }
    return j;
}

// 检查字典中是否存匹配给定前缀的字符串
bool StartsWith(Trie *t, char *s) { return Match(t, s) != -1; }

// 检查字符串是否在树中
bool Has(Trie *t, char *s) {
    if (t == NULL) return false;
    int j = Match(t, s);
    return j != -1 && t->end[j];  // 完全匹配，必须是单词结尾
}

// 公共前缀，输出到 s 中
void CommonPrefix(Trie *t, char *s) {
    if (t == NULL) return;

    int i = 0;
    int j = 0;

    while (1) {
        int k0 = -1;  // 唯一的孩子

        for (int k = 0; k < 26; k++) {
            // 第一次分叉处即公共前缀末尾
            if (t->a[j][k] != -1) {
                if (k0 != -1) return;
                k0 = k;  // 找到唯一的孩子
            }
        }

        if (k0 == -1) return;  // 无孩子，结束

        s[i++] = 'a' + k0;  // 拷贝字符
        j = t->a[j][k0];
    }
}

int main(void) {
    Trie *t = &(Trie){};
    Init(t);
    Put(t, "abcd");
    Put(t, "abde");
    assert(Has(t, "abcd"));
    assert(!Has(t, "abce"));
    assert(StartsWith(t, "abc"));
    assert(StartsWith(t, "abd"));
    assert(!StartsWith(t, "abe"));

    Trie *t1 = &(Trie){};
    Init(t1);
    Put(t1, "abcd");
    Put(t1, "abcefg");
    Put(t1, "abcdefg");
    Put(t1, "abcmn");
    char s[32] = {0};
    CommonPrefix(t1, s);
    assert(s[0] == 'a');
    assert(s[1] == 'b');
    assert(s[2] == 'c');
    assert(s[3] == '\0');
    return 0;
}
