// 二叉树和常见算法问题

#include "tree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/queue.h"
#include "util/stack.h"

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

// 给第 i 个节点创建树
TreeNode *NewTreeI(int a[], int n, int i) {
    if (i < n) {
        int v = a[i];
        if (v == -1) return NULL;  // -1 表示空节点

        TreeNode *node = NewTreeNode(v);
        if (node == NULL) return NULL;

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
void LevelOrder(TreeNode *root) {
    Queue *q = NewQueue();
    QueuePush(q, root);

    while (!IsQueueEmpty(q)) {
        // 队列中的节点是当前层次中的节点
        int qsize = QueueSize(q);
        for (int j = 0; j < qsize; j++) {
            TreeNode *node = QueuePop(q);
            if (node == NULL) continue;

            PrintTreeNode(node);

            QueuePush(q, node->left);
            QueuePush(q, node->right);
        }
        PrintNewline();  // 打印一层
    }

    FreeQueue(q);
}

// 前序遍历 - 非递归
void PreOrderII(TreeNode *root) {
    Stack *s = NewStack();
    StackPush(s, root);

    while (!IsStackEmpty(s)) {
        TreeNode *node = StackPop(s);

        if (node == NULL) continue;

        PrintTreeNode(node);

        StackPush(s, node->right);
        StackPush(s, node->left);
    }

    FreeStack(s);
}
