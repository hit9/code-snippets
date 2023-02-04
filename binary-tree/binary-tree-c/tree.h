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

// 树节点函数声明

TreeNode *NewTreeNode(int v);       // 创建树节点
void FreeTreeNode(TreeNode *node);  // 释放树节点

// 二叉树函数声明

TreeNode *NewTree(int a[], int n);  // 从数组构建树
void FreeTree(TreeNode *root);      // 释放整个树

///////////
// 遍历
//////////

// 辅助数据结构 - 树节点包装
typedef struct _Wrapper {
    TreeNode *node;
    bool visited;
} TreeNodeWrapper;

// 树节点包装的函数声明
TreeNodeWrapper *NewTreeNodeWrapper(TreeNode *node, bool visited);
void FreeTreeNodeWrapper(TreeNodeWrapper *w);

void BFS(TreeNode *root);         // BFS 广度优先遍历 - 打印
void PreOrder(TreeNode *root);    // DFS 前序遍历 - 打印 递归版本
void InOrder(TreeNode *root);     // DFS 中序遍历 - 打印 递归版本
void PostOrder(TreeNode *root);   // DFS 后序遍历 - 打印 递归版本
void LevelOrder(TreeNode *root);  // 层序遍历 - 打印

void PreOrderII(TreeNode *root);   // 前序遍历 - 打印 非递归
void InOrderII(TreeNode *root);    // 中序遍历 - 打印 非递归
void PostOrderII(TreeNode *root);  // 后序遍历 - 打印 非递归

/////////////
// 简单问题
/////////////

int Count(TreeNode *root);               // 计算节点数
int MaxDepth(TreeNode *root);            // 最大深度
int MinDepth(TreeNode *root);            // 最小深度
bool Compare(TreeNode *a, TreeNode *b);  // 比较两个树是否相等
bool IsSymmetric(TreeNode *root);        // 是否对称
bool IsBalanced(TreeNode *root);         // 是否平衡
TreeNode *Invert(TreeNode *root);        // 翻转二叉树
TreeNode *Find(TreeNode *root, int v);   // 查找
TreeNode *LowestCommonAncestor(TreeNode *root, TreeNode *p,
                               TreeNode *q);    // 最低公共祖先
bool IsSubStructure(TreeNode *a, TreeNode *b);  // 判断子结构
TreeNode *Flatten(TreeNode *root);              // 先序展开为链表

////////////////
// 序列化到数组
////////////////

IntArray *ToArray(TreeNode *root);    // 转化为数组 广度优先
TreeNode *FromArray(int a[], int n);  // 从数组建树 广度优先

////////////////
// 二叉搜索树
////////////////

bool IsBST1(TreeNode *root);               // 是否二叉搜索树
TreeNode *BSTFind(TreeNode *root, int v);  // 二叉搜索树的查找
int BSTKth1(TreeNode *root, int k);  // 找出二叉搜索树的第 k 小元素的值 递归
int BSTKth2(TreeNode *root, int k);  // 找出二叉搜索树的第 k 小元素的值 非递归
TreeNode *BSTLowestCommonAncestor(TreeNode *root, TreeNode *p,
                                  TreeNode *q);  // 二叉搜索树的最近公共祖先

// IsBST2 的辅助数据结构
typedef struct _IsBST2HelperLast {
    int v;      // 上一次遍历节点的值
    bool init;  // last->val 是否已经初始化
} IsBST2HelperLast;

bool IsBST2(TreeNode *root);  // 是否二叉搜索树
