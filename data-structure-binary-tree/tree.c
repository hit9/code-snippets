// 二叉树和常见算法问题

#include "tree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/queue.h"

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

// 给第 i 个节点创建树
TreeNode *NewTreeI(int a[], int n, int i) {
    if (i < n) {
        int v = a[i];
        if (v == -1) return NULL;  // -1 表示空节点
        TreeNode *node = NewTreeNode(v);
        node->v = v;
        node->left = NewTreeI(a, n, 2 * i + 1);   // 左孩子
        node->right = NewTreeI(a, n, 2 * i + 2);  // 右孩子
        return node;
    }
    return NULL;
}

// 从数组构建一个树
//
// [0 1 2 3 4 5 -1 6 7] =>
//
//      0
//    1   2
//   3 4 5 -1
//  6 7
TreeNode *NewTree(int a[], int n) { return NewTreeI(a, n, 0); }

// 释放整个树的内存
void FreeTree(TreeNode *root) {
    if (root == NULL) return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

void PrintTreeNode(TreeNode *node) { printf("%d ", node->v); }

// 前序遍历 - 递归
void PreOrderTraversal(TreeNode *root) {
    if (root == NULL) return;
    PrintTreeNode(root);  // 当前节点处理在前
    PreOrderTraversal(root->left);
    PreOrderTraversal(root->right);
}

// 中序遍历 - 递归
void InOrderTraversal(TreeNode *root) {
    if (root == NULL) return;
    InOrderTraversal(root->left);
    PrintTreeNode(root);  // 当前节点处理在中间
    InOrderTraversal(root->right);
}

// 后序遍历 - 递归
void PostOrderTraversal(TreeNode *root) {
    if (root == NULL) return;
    PostOrderTraversal(root->left);
    PostOrderTraversal(root->right);
    PrintTreeNode(root);  // 当前节点处理在后
}

// 层序遍历
void LevelOrderTraversal(TreeNode *root) {
    if (root == NULL) return;

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
