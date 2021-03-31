// 二叉树和常见算法问题

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

void PreOrderTraversal(TreeNode *root);   // 前序遍历 递归
void InOrderTraversal(TreeNode *root);    // 中序遍历 递归
void PostOrderTraversal(TreeNode *root);  // 后序遍历 递归

void PreOrderTraversalNonRecur(TreeNode *root);  // 前序遍历 非递归

void LevelOrderTraversal(TreeNode *root);  // 层序遍历
