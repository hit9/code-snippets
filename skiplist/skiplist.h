// 跳跃表的实现
//
//  Level[0]: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> nil
//  Level[1]: 1 -> 2 -> 4 -> 5 -> 7 -> 8 -> 9 -> nil
//  Level[2]: 2 -> 4 -> 5 -> 7 -> 9 -> nil
//  Level[3]: 4 -> 5 -> 7 -> 9 -> nil
//  Level[4]: 4 -> 7 -> nil

#include <stdbool.h>  // for bool
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
