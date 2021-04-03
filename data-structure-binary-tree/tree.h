// 二叉树和常见算法问题

#include <stdbool.h>

#include "util.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// 树的节点
typedef struct _TreeNode {
    int v;  // 数据
    struct _TreeNode *left;
    struct _TreeNode *right;
} TreeNode;

// 辅助数据结构 - 树节点包装
typedef struct _Wrapper {
    TreeNode *node;
    bool visited;
} TreeNodeWrapper;

// 树节点函数声明

TreeNode *NewTreeNode(int v);       // 创建树节点
void FreeTreeNode(TreeNode *node);  // 释放树节点

// 二叉树函数声明

TreeNode *NewTree(int a[], int n);  // 从数组构建树
void FreeTree(TreeNode *root);      // 释放整个树

void BFS(TreeNode *root);         // BFS 广度优先遍历 - 打印
void PreOrder(TreeNode *root);    // DFS 前序遍历 - 打印 递归版本
void InOrder(TreeNode *root);     // DFS 中序遍历 - 打印 递归版本
void PostOrder(TreeNode *root);   // DFS 后序遍历 - 打印 递归版本
void LevelOrder(TreeNode *root);  // 层序遍历 - 打印

void PreOrderII(TreeNode *root);   // 前序遍历 - 打印 非递归
void InOrderII(TreeNode *root);    // 中序遍历 - 打印 非递归
void PostOrderII(TreeNode *root);  // 后序遍历 - 打印 非递归

int Count(TreeNode *root);               // 计算节点数
int MaxDepth(TreeNode *root);            // 最大深度
int MinDepth(TreeNode *root);            // 最小深度
bool Compare(TreeNode *a, TreeNode *b);  // 比较两个树是否相等
bool IsSymmetric(TreeNode *root);        // 是否对称
bool IsBalanced(TreeNode *root);         // 是否平衡
bool IsBST1(TreeNode *root);             // 是否二叉搜索树
bool IsBST2(TreeNode *root);             // 是否二叉搜索树

IntArray *ToArray(TreeNode *root);    // 转化为数组 广度优先
TreeNode *FromArray(int a[], int n);  // 从数组建树 广度优先

// 树节点包装的函数声明
TreeNodeWrapper *NewTreeNodeWrapper(TreeNode *node, bool visited);
void FreeTreeNodeWrapper(TreeNodeWrapper *w);
