// 二叉树和常见算法问题

#include "tree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//  Utils
void PrintTreeNode(TreeNode *node) {
    if (node != NULL) printf("%d ", node->v);
}

void PrintNewline() { printf("\n"); }

/////////
// 实现
/////////

// 创建节点
TreeNode *NewTreeNode(int v) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->v = v;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 释放节点
void FreeTreeNode(TreeNode *node) { free(node); }

// 从数组构建一个树
//
// [0 1 2 3 4 5 -1 6 7] =>
//
//      0
//    1   2
//   3 4 5
//  6 7
//
//  [0, -1, 2, -1, 3 -1, 4] =>
//
//      0
//        2
//           3
//              4
TreeNode *NewTree(int a[], int n) { return FromArray(a, n); }

// 释放整个树的内存
void FreeTree(TreeNode *root) {
    if (root == NULL) return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

// 前序遍历 - 递归
void PreOrder(TreeNode *root) {
    if (root == NULL) return;
    PrintTreeNode(root);  // 当前节点处理在前
    PreOrder(root->left);
    PreOrder(root->right);
}

// 中序遍历 - 递归
void InOrder(TreeNode *root) {
    if (root == NULL) return;
    InOrder(root->left);
    PrintTreeNode(root);  // 当前节点处理在中间
    InOrder(root->right);
}

// 后序遍历 - 递归
void PostOrder(TreeNode *root) {
    if (root == NULL) return;
    PostOrder(root->left);
    PostOrder(root->right);
    PrintTreeNode(root);  // 当前节点处理在后
}

// 广度优先遍历 - 队列 + 循环
void BFS(TreeNode *root) {
    Queue *q = NewQueue();
    QueuePush(q, root);

    while (!IsQueueEmpty(q)) {
        TreeNode *node = QueuePop(q);

        if (node == NULL) continue;

        PrintTreeNode(node);

        QueuePush(q, node->left);
        QueuePush(q, node->right);
    }

    FreeQueue(q);
}

// 层序遍历
// https://leetcode-cn.com/problems/binary-tree-level-order-traversal/
void LevelOrder(TreeNode *root) {
    Queue *q = NewQueue();

    if (root != NULL) QueuePush(q, root);

    while (!IsQueueEmpty(q)) {
        // 队列中的节点是当前层次中的节点
        int qsize = QueueSize(q);

        for (int j = 0; j < qsize; j++) {
            TreeNode *node = QueuePop(q);
            if (node == NULL) continue;

            PrintTreeNode(node);

            if (node->left != NULL) QueuePush(q, node->left);
            if (node->right != NULL) QueuePush(q, node->right);
        }
        PrintNewline();  // 打印一层
    }

    FreeQueue(q);
}

// 前序遍历 - 非递归
void PreOrderII(TreeNode *root) {
    Stack *s = NewStack();
    StackPush(s, NewTreeNodeWrapper(root, false));

    while (!IsStackEmpty(s)) {
        TreeNodeWrapper *w = StackPop(s);

        bool visited = w->visited;
        TreeNode *node = w->node;

        FreeTreeNodeWrapper(w);

        if (node == NULL) continue;

        if (!visited) {
            StackPush(s, NewTreeNodeWrapper(node->right, false));
            StackPush(s, NewTreeNodeWrapper(node->left, false));
            StackPush(s, NewTreeNodeWrapper(node, true));
        } else {
            PrintTreeNode(node);
        }
    }

    FreeStack(s);
}

// 中序遍历 - 非递归
void InOrderII(TreeNode *root) {
    Stack *s = NewStack();
    StackPush(s, NewTreeNodeWrapper(root, false));

    while (!IsStackEmpty(s)) {
        TreeNodeWrapper *w = StackPop(s);

        TreeNode *node = w->node;
        bool visited = w->visited;
        FreeTreeNodeWrapper(w);

        if (node == NULL) continue;

        if (!visited) {
            StackPush(s, NewTreeNodeWrapper(node->right, false));
            StackPush(s, NewTreeNodeWrapper(node, true));
            StackPush(s, NewTreeNodeWrapper(node->left, false));
        } else {
            PrintTreeNode(node);
        }
    }

    FreeStack(s);
}

// 后序遍历 - 非递归
void PostOrderII(TreeNode *root) {
    Stack *s = NewStack();
    StackPush(s, NewTreeNodeWrapper(root, false));

    while (!IsStackEmpty(s)) {
        TreeNodeWrapper *w = StackPop(s);

        bool visited = w->visited;
        TreeNode *node = w->node;

        FreeTreeNodeWrapper(w);

        if (node == NULL) continue;

        if (!visited) {
            StackPush(s, NewTreeNodeWrapper(node, true));
            StackPush(s, NewTreeNodeWrapper(node->right, false));
            StackPush(s, NewTreeNodeWrapper(node->left, false));
        } else {
            PrintTreeNode(node);
        }
    }

    FreeStack(s);
}

TreeNodeWrapper *NewTreeNodeWrapper(TreeNode *node, bool visited) {
    TreeNodeWrapper *w = malloc(sizeof(TreeNodeWrapper));
    w->node = node;
    w->visited = visited;
    return w;
}

void FreeTreeNodeWrapper(TreeNodeWrapper *w) { free(w); }

// 返回节点数量
int Count(TreeNode *root) {
    if (root == NULL) return 0;
    return 1 + Count(root->left) + Count(root->right);
}

// 返回最大深度
//    3
//  9   20
//    15  7
// => MaxDepth = 3
// https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/
int MaxDepth(TreeNode *root) {
    if (root == NULL) return 0;
    int max_depth_left = MaxDepth(root->left);
    int max_depth_right = MaxDepth(root->right);
    return MAX(max_depth_left, max_depth_right) + 1;
}

// 返回最小深度
//    3
//  9   20
//    15  7
// => MinDepth = 2
// 根节点到最近的叶子节点的节点数量
// https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/
int MinDepth(TreeNode *root) {
    if (root == NULL) return 0;

    int min_depth_left = MinDepth(root->left);
    int min_depth_right = MinDepth(root->right);

    if (root->left == NULL) return min_depth_right + 1;
    if (root->right == NULL) return min_depth_left + 1;
    return MIN(min_depth_left, min_depth_right) + 1;
}

// 比较两个二叉树是否完全相等
bool Compare(TreeNode *a, TreeNode *b) {
    if (a == NULL && b == NULL)
        return true;
    else if (a == NULL && b != NULL)
        return false;
    else if (a != NULL && b == NULL)
        return false;
    else {
        return a->v == b->v && Compare(a->left, b->left) &&
               Compare(a->right, b->right);
    }
}

// 二叉树转化为数组
//
//    2
//  3   4
//    5   6
//          7
// => [2,3,4,-1,5,6,-1,-1,-1,7]
//
//    2
//      3
//        4
// => [2,-1,3,-1,4]
//
// 采用广度优先遍历
IntArray *ToArray(TreeNode *root) {
    IntArray *a = NewIntArray();

    Queue *q = NewQueue();
    QueuePush(q, root);

    int ec = 0;  // 记录自上一个非空节点以后的空节点数量

    while (!IsQueueEmpty(q)) {
        // 依次处理完本层节点
        TreeNode *node = QueuePop(q);

        if (node == NULL) {
            ec++;
            continue;
        } else {
            // 把前面的空节点放进来
            // 为了防止数据末尾有 -1，所以遇到非空节点是才把-1刷出来
            for (int i = 0; i < ec; i++) IntArrayPush(a, -1);
            ec = 0;
            // 添加当前非空节点的数据
            IntArrayPush(a, node->v);
            // 添加下一层节点到队列
            QueuePush(q, node->left);
            QueuePush(q, node->right);
        }
    }

    FreeQueue(q);
    return a;
}

// 数组转化为树 （即 ToArray 的逆）
TreeNode *FromArray(int a[], int n) {
    if (n <= 0) return NULL;
    if (a[0] == -1) return NULL;

    Queue *q = NewQueue();  // 记录上一层节点
    TreeNode *root = NewTreeNode(a[0]);
    QueuePush(q, root);

    int i = 1;
    int v;

    while (!IsQueueEmpty(q)) {
        TreeNode *node = QueuePop(q);

        if (i < n) {  // 新建左节点
            v = a[i++];
            if (v != -1) node->left = NewTreeNode(v);
        }

        if (i < n) {  // 新建右节点
            v = a[i++];
            if (v != -1) node->right = NewTreeNode(v);
        }

        if (node->left != NULL) QueuePush(q, node->left);
        if (node->right != NULL) QueuePush(q, node->right);
    }

    FreeQueue(q);
    return root;
}
