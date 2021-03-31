// 二叉树和常见算法问题

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

//////////
// 测试
//////////

void TestBFS() {
    printf("bfs:");
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    BFS(root);
    printf("\n");
    FreeTree(root);
}

void TestPreOrder() {
    printf("pre order i:");
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    PreOrder(root);
    printf("\n");
    FreeTree(root);
}

void TestPreOrderII() {
    printf("pre order ii:");
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    PreOrderII(root);
    printf("\n");
    FreeTree(root);
}

void TestInOrder() {
    printf("in order i:");
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    InOrder(root);
    printf("\n");
    FreeTree(root);
}

void TestInOrderII() {
    printf("in order ii:");
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    InOrderII(root);
    printf("\n");
    FreeTree(root);
}

void TestPostOrder() {
    printf("post order i:");
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    PostOrder(root);
    printf("\n");
    FreeTree(root);
}

void TestLevelOrder() {
    printf("level order:");
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);
    printf("\n");
    LevelOrder(root);
    FreeTree(root);
}

int main(void) {
    TestBFS();
    TestPreOrder();
    TestPreOrderII();
    TestInOrder();
    TestInOrderII();
    TestPostOrder();
    TestLevelOrder();
    return 0;
}
