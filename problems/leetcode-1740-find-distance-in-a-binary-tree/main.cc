// https://leetcode.cn/problems/find-distance-in-a-binary-tree
// 1740. 找到二叉树中的距离
// 给定一棵二叉树的根节点 root 以及两个整数 p 和 q ，返回该二叉树中值为 p 的结点与值为 q 的结点间的 距离 。
// 两个结点间的 距离 就是从一个结点到另一个结点的路径上边的数目。

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    // 返回深度，如果是 -1 表示不存在
    int depth(TreeNode *root, int p) {
        if (root->val == p) return 0;

        // 检查左子树
        if (root->left != nullptr) {
            int d = depth(root->left, p);
            if (d >= 0) return d + 1;
        }

        // 检查右子树
        if (root->right != nullptr) {
            int d = depth(root->right, p);
            if (d >= 0) return d + 1;
        }
        // 都找不到就是 -1
        return -1;
    };
    int findDistance(TreeNode *root, int p, int q) {
        if (p == q) return 0;
        if (root == nullptr) return 0;
        // 其中一个是根的情况, 距离即到另一个节点的深度
        if (root->val == p) return depth(root, q);
        if (root->val == q) return depth(root, p);
        if (root->left == nullptr && root->right == nullptr) return 0;
        // 如果都在左孩子中, 则向左子树递归
        if (root->left != nullptr && depth(root->left, p) >= 0 &&
            depth(root->left, q) >= 0)
            return findDistance(root->left, p, q);
        // 如果都在右孩子中, 则向右子树递归
        else if (root->right != nullptr && depth(root->right, p) >= 0 &&
                 depth(root->right, q) >= 0)
            return findDistance(root->right, p, q);
        // 在左右两侧
        return depth(root, p) + depth(root, q);
    }
};
