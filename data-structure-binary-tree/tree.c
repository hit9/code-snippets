// 二叉树和常见算法问题

#include "tree.h"

#include <limits.h>
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

/////////
// 遍历
/////////

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

/////////
// 简单问题
/////////

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

// 判断两个树是否镜像相等
// 为 IsSymmetric 的辅助函数
//
//    2        2
//  3   4    4   3
// 5 6 7 8  8 7 6 5
// 两个树是镜像相等的
bool IsTwoTreeSymmetric(TreeNode *a, TreeNode *b) {
    if (a == NULL && b == NULL)
        return true;
    else if (a != NULL && b == NULL)
        return false;
    else if (a == NULL && b != NULL)
        return false;
    else {
        return a->v == b->v && IsTwoTreeSymmetric(a->left, b->right) &&
               IsTwoTreeSymmetric(a->right, b->left);
    }
}

// 判断一个二叉树是否对称
//
//    1
//  2   2
// 3 4 4 3
// => true
bool IsSymmetric(TreeNode *root) {
    if (root == NULL) return true;
    return IsTwoTreeSymmetric(root->left, root->right);
}

// 翻转二叉树
//
//    2
//  3   4
// 5 6 7
// =>
//    2
//  4   3
// 7   6 5
TreeNode *Invert(TreeNode *root) {
    if (root == NULL) return NULL;
    TreeNode *left = root->left;
    TreeNode *right = root->right;
    root->right = Invert(left);
    root->left = Invert(right);
    return root;
}

// 查找值为 v 的节点
TreeNode *Find(TreeNode *root, int v) {
    if (root == NULL) return NULL;
    if (root->v == v) return root;
    TreeNode *left = Find(root->left, v);
    TreeNode *right = Find(root->right, v);
    if (left != NULL) return left;
    if (right != NULL) return right;
    return NULL;
}

// 找出 p 和 q 的最低公共祖先
//
//         3
//      5     2
//    1  6   0  8
//      7 4
//
//    p=7, q=8 => 3
TreeNode *LowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (root == NULL) return NULL;
    if (p == root || q == root) return root;

    // LowestCommonAncestor 函数的作用：
    // 如果 p 和 q 都在树中，则返回其最近的公共祖先节点
    // 如果其中一个在树中，另一个不在，则返回这个节点
    // 如果都不在树中，返回 NULL
    TreeNode *left = LowestCommonAncestor(root->left, p, q);
    TreeNode *right = LowestCommonAncestor(root->right, p, q);

    if (left != NULL && right != NULL)
        return root;
    else if (left != NULL && right == NULL)
        return left;
    else if (left == NULL && right != NULL)
        return right;
    else
        return NULL;
}

// 函数 IsSubStructure 的辅助函数
// 判断树 b 是否是 a 的前缀子树
// 即必须在根节点处匹配
bool IsSubStructureHelper(TreeNode *a, TreeNode *b) {
    if (b == NULL) return true;
    if (a == NULL) return false;
    if (a->v != b->v) return false;
    return IsSubStructureHelper(a->left, b->left) &&
           IsSubStructureHelper(a->right, b->right);
}

// 判断二叉树 b 是否是 a 的子结构
//
//    例如
//                4
//       a    2       3
//          4   5   6   7
//         8 9
//
//            4
//       b   8 9
//       => True
//
//    约定：空树不是任何树的子结构
bool IsSubStructure(TreeNode *a, TreeNode *b) {
    if (b == NULL) return false;
    if (a == NULL) return false;
    return IsSubStructureHelper(a, b) || IsSubStructure(a->left, b) ||
           IsSubStructure(a->right, b);
}

// Flatten 的辅助函数
// 展开给定的二叉树，返回展开后的尾巴节点（非空）
// 如果树是空的，才返回空节点
TreeNode *FlattenHelper(TreeNode *root) {
    if (root == NULL) return NULL;
    // 左右都空，链表尾巴是 root
    if (root->left == NULL && root->right == NULL) return root;
    // 左空右不空，展开右边，返回其尾巴
    if (root->left == NULL && root->right != NULL)
        return FlattenHelper(root->right);
    // 左不空，右空
    if (root->left != NULL && root->right == NULL) {
        // 展开左边，挂在右孩子上，返回其尾巴
        TreeNode *tail = FlattenHelper(root->left);
        root->right = root->left;
        root->left = NULL;
        return tail;
    }
    // 左右都不空
    // 展开左右链表
    TreeNode *left_tail = FlattenHelper(root->left);
    TreeNode *right_tail = FlattenHelper(root->right);

    // 右侧链表挂在左侧链表后面
    left_tail->right = root->right;
    left_tail->left = NULL;

    // 拼接后的大链表挂在 root 的右孩子位置上
    root->right = root->left;
    root->left = NULL;

    // 返回右孩子链表的尾巴
    return right_tail;
}

// 将二叉树展开为链表，先序顺序
//
//         1                  1
//      2     5        =>      2
//    3   4     6               3
//                               4
//                                5
//                                 6
TreeNode *Flatten(TreeNode *root) {
    FlattenHelper(root);
    return root;
}

/////////
// 序列化
/////////

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

// IsBalanced 函数的辅助函数
// 如果树是平衡树，返回其最大深度
// 否则，返回 -1
int IsBalancedHelperDepth(TreeNode *root) {
    if (root == NULL) return 0;
    int d1 = IsBalancedHelperDepth(root->left);
    int d2 = IsBalancedHelperDepth(root->right);
    if (d1 == -1 || d2 == -1) return -1;
    if (abs(d1 - d2) > 1) return -1;
    return MAX(d1, d2) + 1;
}

// 判断平衡树
// 二叉树中任意节点的左右子树的深度相差不超过1 为平衡树
bool IsBalanced(TreeNode *root) { return IsBalancedHelperDepth(root) != -1; }

/////////
// 二叉搜索树
/////////

// IsBST1 的辅助函数
bool IsBST1Helper(TreeNode *root, long long upper, long long lower) {
    if (root == NULL) return true;
    if (root->v <= lower || root->v >= upper) return false;
    return IsBST1Helper(root->left, root->v, lower) &&
           IsBST1Helper(root->right, upper, root->v);
}

// 判断二叉搜索树
// 二叉搜索树的特征：
// 1. 节点的左子树只包含小于当前节点的数
// 2. 节点的右子树只包含大于当前节点的数
// 3. 所有左子树和右子树自身必须也是二叉搜索树
// 这是第一种方法：递归验证上下界
bool IsBST1(TreeNode *root) { return IsBST1Helper(root, LONG_MAX, LONG_MIN); }

// IsBST2Helper 的辅助函数，中序遍历判断是否递增
bool IsBST2Helper(TreeNode *root, IsBST2HelperLast *last) {
    if (root == NULL) return true;
    if (!IsBST2Helper(root->left, last)) return false;

    if (last->init && root->v <= last->v) return false;

    last->v = root->v;
    last->init = true;

    if (!IsBST2Helper(root->right, last)) return false;
    return true;
}

// 判断二叉搜索树
// 这时第二种方法：中序遍历有序
bool IsBST2(TreeNode *root) {
    IsBST2HelperLast last = {0, false};
    return IsBST2Helper(root, &last);
}

// 二叉搜索树的查找
TreeNode *BSTFind(TreeNode *root, int v) {
    if (root == NULL) return NULL;
    if (root->v == v)
        return root;
    else if (root->v > v)
        return BSTFind(root->left, v);
    else if (root->v < v)
        return BSTFind(root->right, v);
    return NULL;
}

// BSTKth1 的辅助函数
void BSTKth1Helper(TreeNode *root, IntArray *a, int k) {
    if (root == NULL) return;
    if (IntArraySize(a) >= k) return;  // 终止无效递归
    BSTKth1Helper(root->left, a, k);
    IntArrayPush(a, root->v);
    BSTKth1Helper(root->right, a, k);
}

// 找出二叉搜索树的第 k 小的元素
// 递归版
// 性质：二叉搜索树的中序遍历是有序的
int BSTKth1(TreeNode *root, int k) {
    IntArray *a = NewIntArray();
    BSTKth1Helper(root, a, k);
    int v = IntArrayUnwrap(a)[k - 1];
    FreeIntArray(a);
    return v;
}

// 找出二叉搜索树的第 k 小的元素
// 非递归版
int BSTKth2(TreeNode *root, int k) {
    if (root == NULL) return -1;

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
            k--;
            if (k == 0) return node->v;
        }
    }
    FreeStack(s);
    return -1;
}

// 二叉搜索树的最近公共祖先
TreeNode *BSTLowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (root == NULL) return NULL;
    if (root->v < p->v && root->v < q->v)
        // p 和 q 都在右子树
        return BSTLowestCommonAncestor(root->right, p, q);
    if (root->v > p->v && root->v > q->v)
        // p 和 q 都在左子树
        return BSTLowestCommonAncestor(root->left, p, q);
    // p 和 q 分别位于两个子树
    return root;
}
