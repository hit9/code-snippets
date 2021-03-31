// 二叉树和常见算法问题

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

//////////
// 测试
//////////

void TestNewTree() {
    int a[] = {0, 1, 2, 3, -1, -1, 6, 7, 8, -1};
    TreeNode *root = NewTree(a, 10);
    BFS(root);
    printf("\n");
    FreeTree(root);
}

void TestPreOrder() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    PreOrder(root);
    printf("\n");
    FreeTree(root);
}

void TestPreOrderII() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    PreOrderII(root);
    printf("\n");
    FreeTree(root);
}

void TestInOrder() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    InOrder(root);
    printf("\n");
    FreeTree(root);
}

void TestPostOrder() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    PostOrder(root);
    printf("\n");
    FreeTree(root);
}

void TestLevelOrder() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    LevelOrder(root);
    printf("\n");
    FreeTree(root);
}

int main(void) {
    TestNewTree();
    TestPreOrder();
    TestPreOrderII();
    TestInOrder();
    TestPostOrder();
    TestLevelOrder();
    return 0;
}
