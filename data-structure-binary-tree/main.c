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
    LevelOrderTraversal(root);
    printf("\n");
    FreeTree(root);
}

// 仅测试打印
void TestTraversal() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);

    printf("前序：");
    PreOrderTraversal(root);
    printf("\n");

    printf("中序：");
    InOrderTraversal(root);
    printf("\n");

    printf("后序：");
    PostOrderTraversal(root);
    printf("\n");

    printf("层序：");
    LevelOrderTraversal(root);
    printf("\n");

    printf("前序（非递归）：");
    PreOrderTraversalNonRecur(root);
    printf("\n");

    FreeTree(root);
}

int main(void) {
    TestNewTree();
    TestTraversal();

    return 0;
}
