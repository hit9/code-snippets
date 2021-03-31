// 二叉树和常见算法问题

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

//////////
// 测试
//////////

// 仅测试打印
void TestTraversal() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *root = NewTree(a, 10);

    PreOrderTraversal(root);
    printf("\n");
    InOrderTraversal(root);
    printf("\n");
    PostOrderTraversal(root);
    printf("\n");
    LevelOrderTraversal(root);
    printf("\n");

    FreeTree(root);
}

int main(void) {
    TestTraversal();

    return 0;
}
