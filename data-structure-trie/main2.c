// 字典树
// https://zh.wikipedia.org/zh-hans/Trie

// 动态内存版

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

// 字典树 - 动态内存
typedef struct _Trie {
    struct _Trie *next[26];  // 后继节点
    bool end;                // 是否单词结尾
} Trie;

Trie *NewTrie() {
    Trie *t = malloc(sizeof(Trie));
    for (int i = 0; i < 26; i++) t->next[i] = NULL;
    t->end = false;
    return t;
}

void FreeTrie(Trie *t) {
    if (t != NULL) {
        for (int k = 0; k < 26; k++) FreeTrie(t->next[k]);
        free(t);
    }
}

// 添加字符串
void Put(Trie *t, char *s) {
    if (t == NULL) return;

    for (int i = 0; s[i] != '\0'; i++) {
        int k = s[i] - 'a';
        if (t->next[k] == NULL) {
            t->next[k] = NewTrie();
        }
        t = t->next[k];
    }
    t->end = true;
}

// 前缀匹配，返回最后一个节点
// 如果未匹配，返回 -1
Trie *Match(Trie *t, char *s) {
    if (t == NULL) return NULL;

    for (int i = 0; s[i] != '\0'; i++) {
        int k = s[i] - 'a';
        if (t->next[k] == NULL) return NULL;
        t = t->next[k];
    }
    return t;
}

// 检查字典中是否存匹配给定前缀的字符串
bool StartsWith(Trie *t, char *s) { return Match(t, s) != NULL; }

// 检查字符串是否在树中
bool Has(Trie *t, char *s) {
    if (t == NULL) return false;
    Trie *j = Match(t, s);
    return j != NULL && j->end;  // 完全匹配，必须是单词结尾
}

// 公共前缀，输出到 s 中
void CommonPrefix(Trie *t, char *s) {
    if (t == NULL) return;

    int i = 0;

    while (1) {
        int k0 = -1;  // 唯一的孩子

        for (int k = 0; k < 26; k++) {
            // 第一次分叉处即公共前缀末尾
            if (t->next[k] != NULL) {
                if (k0 != -1) return;
                k0 = k;  // 找到唯一的孩子
            }
        }

        if (k0 == -1) return;  // 无孩子，结束

        s[i++] = 'a' + k0;  // 拷贝字符

        t = t->next[k0];
    }
}

int main(void) {
    Trie *t = NewTrie();
    Put(t, "abcd");
    Put(t, "abde");
    assert(Has(t, "abcd"));
    assert(!Has(t, "abce"));
    assert(StartsWith(t, "abc"));
    assert(StartsWith(t, "abd"));
    assert(!StartsWith(t, "abe"));
    FreeTrie(t);

    Trie *t1 = NewTrie();
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
    FreeTrie(t1);
    return 0;
}
