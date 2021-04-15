// 跳跃表的实现
//
//  Level[0]: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> nil
//  Level[1]: 1 -> 2 -> 4 -> 5 -> 7 -> 8 -> 9 -> nil
//  Level[2]: 2 -> 4 -> 5 -> 7 -> 9 -> nil
//  Level[3]: 4 -> 5 -> 7 -> 9 -> nil
//  Level[4]: 4 -> 7 -> nil

#include <stdbool.h>  // for bool
#include <stdio.h>    // for printf
#include <stdlib.h>   // for rand, malloc

// 声明

#define MAX_LEVEL 16  // 最大的层数

typedef struct _Node {
    int v;                           // 节点数据
    int level;                       // 节点的总层数
    struct _Node *nexts[MAX_LEVEL];  // 前进数组, 元素索引: 0~level
} Node;

typedef struct {
    int n;       // 节点数
    int level;   // 最大层度
    Node *head;  // 头节点 非数据节点 且 层数最高
} Skiplist;

int RandLevel();  // 生成新节点层数

Node *NewNode(int v, int level);  // 创建节点
void FreeNode(Node *node);        // 释放节点

Skiplist *NewSkiplist();          // 创建
void FreeSkiplist(Skiplist *sl);  // 是否
void Put(Skiplist *sl, int v);    // 添加
bool Has(Skiplist *sl, int v);    // 是否包含
bool Pop(Skiplist *sl, int v);    // 删除
int Top(Skiplist *sl);            // 查头
int PopFirst(Skiplist *sl);       // 删除头
int Len(Skiplist *sl);            // 长度
void Print(Skiplist *sl);         // 打印

/////////
// 实现
////////

// 生成一个 1 到 MAX_LEVEL 之间的随机层数
int RandLevel() {
    int level = 1;
    // 以概率 P 递增 level
    // 1/2 的概率 level → 1
    // 1/4 的概率 level → 2
    // 1/8 的概率 level → 3
    while ((rand() & 65535) * 1.0 / 65535 < 0.5) level++;
    return level < MAX_LEVEL ? level : MAX_LEVEL;
}

// 新建一个节点
Node *NewNode(int v, int level) {
    Node *node = malloc(sizeof(Node));
    if (node != NULL) {
        node->v = v;
        node->level = level;
        for (int i = 0; i < MAX_LEVEL; i++) node->nexts[i] = NULL;
    }
    return node;
}

// 释放一个节点
void FreeNode(Node *node) {
    if (node != NULL) free(node);
}

// 新建一个跳跃表
Skiplist *NewSkiplist() {
    Skiplist *sl = malloc(sizeof(Skiplist));
    if (sl != NULL) {
        sl->head = NewNode(-1, 1);
        sl->level = 1;
        sl->n = 0;
    }
    return sl;
}

// 释放一个跳跃表
void FreeSkiplist(Skiplist *sl) {
    if (sl != NULL) {
        while (sl->n > 0) PopFirst(sl);
        FreeNode(sl->head);
        free(sl);
    }
}

// 获取元素个数
int Len(Skiplist *sl) {
    if (sl == NULL) return 0;
    return sl->n;
}

// 添加一个元素
void Put(Skiplist *sl, int v) {
    // 第一步 找到各层插入位置

    // last[i] 表示第 i 层的插入位置的前驱节点
    Node *last[MAX_LEVEL];
    Node *n = sl->head;

    for (int i = sl->level - 1; i >= 0; i--) {             // 自顶层向下
        while (n->nexts[i] != NULL && n->nexts[i]->v < v)  // 自左到右比较大小
            n = n->nexts[i];
        last[i] = n;
    }

    // 第二步 生成新节点和层数
    int level = RandLevel();  // 新节点的层数

    if (level > sl->level) {
        // 新节点的层数比原来的都大
        // 需要补充 last 数组高位，将把 head 指向此节点
        for (int i = sl->level; i < level; i++) last[i] = sl->head;
        sl->level = level;
    }

    // 第三步，各层执行插入
    Node *node = NewNode(v, level);
    for (int i = 0; i < level; i++) {
        node->nexts[i] = last[i]->nexts[i];
        last[i]->nexts[i] = node;
    }

    sl->n++;
}

// 返回 v 是否在跳表中
bool Has(Skiplist *sl, int v) {
    Node *n = sl->head;
    for (int i = sl->level; i >= 0; i--) {
        while (n->nexts[i] != NULL && n->nexts[i]->v < v)  // 自左到右比较大小
            n = n->nexts[i];
    }
    n = n->nexts[0];
    return n != NULL && n->v == v;
}

// 从跳表中删除 v
bool Pop(Skiplist *sl, int v) {
    // 第一步 找到各层删除位置的前驱节点

    Node *last[MAX_LEVEL];

    Node *n = sl->head;
    for (int i = sl->level - 1; i >= 0; i--) {
        while (n->nexts[i] != NULL && n->nexts[i]->v < v) n = n->nexts[i];
        last[i] = n;
    }

    // 要删除的节点
    n = n->nexts[0];
    if (n == NULL || n->v != v) return false;

    // 第二步，各层执行删除
    for (int i = sl->level - 1; i >= 0; i--) {
        if (last[i]->nexts[i] == n) last[i]->nexts[i] = n->nexts[i];
    }

    // 第三步，去除删除节点后可能造成的无效层次
    while (sl->level > 1 && sl->head->nexts[sl->level - 1] == NULL) {
        sl->level--;
    }
    sl->n--;
    FreeNode(n);
    return true;
}

// 获取头元素
int Top(Skiplist *sl) {
    if (sl == NULL || sl->n == 0) return -1;
    Node *n = sl->head->nexts[0];
    return n->v;
}

// 取出头元素
int PopFirst(Skiplist *sl) {
    if (sl == NULL || sl->n == 0) return -1;

    Node *n1 = sl->head->nexts[0];  // 第一个元素

    // 删除 n1
    for (int i = sl->level - 1; i >= 0; i--) {
        if (sl->head->nexts[i] == n1) {
            sl->head->nexts[i] = n1->nexts[i];
        }
    }

    // 抹除高位无效层次
    while (sl->level > 1 && sl->head->nexts[sl->level - 1] == NULL) {
        sl->level--;
    }

    int v = n1->v;
    FreeNode(n1);
    return n1->v;
}

void Print(Skiplist *sl) {
    if (sl == NULL) return;

    for (int i = sl->level - 1; i >= 0; i--) {
        Node *n = sl->head->nexts[i];
        printf("Level[%d]: ", i);
        while (n != NULL) {
            printf("%d -> ", n->v);
            n = n->nexts[i];
        }
        printf("Nil\n");
    }
}

/////////
// 测试
////////
int main(void) {
    Skiplist *sl = NewSkiplist();
    for (int i = 1; i < 9; i++) Put(sl, i);
    /* Put(sl, 3); */
    /* Put(sl, 4); */
    /* Put(sl, 5); */
    /* Put(sl, 6); */
    /* Put(sl, 7); */
    /* Put(sl, 8); */
    Print(sl);
    return 0;
}
