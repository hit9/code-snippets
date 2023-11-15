// https://leetcode.cn/problems/maximum-product-of-splitted-binary-tree
// 1339. 分裂二叉树的最大乘积
//
// 给你一棵二叉树，它的根为 root 。请你删除 1
// 条边，使二叉树分裂成两棵子树，且它们子树和的乘积尽可能大。
// 由于答案可能会很大，请你将结果对 10^9 + 7 取模后再返回。

// 思路：建立求和树，然后再 dfs 求最大

#include <algorithm>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

struct SumTreeNode {
    unsigned long long sum;
    SumTreeNode *left;
    SumTreeNode *right;
    SumTreeNode(unsigned long long x, SumTreeNode *left, SumTreeNode *right)
        : sum(x), left(left), right(right) {}
};

class Solution {
   public:
    // 建一个求和树，结构和原来的树一样, 每个节点的值是以其为根节点的树的总和
    SumTreeNode *BuildSumTree(TreeNode *root) {
        if (root == nullptr) return nullptr;
        auto left = BuildSumTree(root->left);
        auto right = BuildSumTree(root->right);
        unsigned long long sum = root->val;
        if (left != nullptr) sum += left->sum;
        if (right != nullptr) sum += right->sum;
        return new SumTreeNode(sum, left, right);
    }

    // 递归断开一边, 求乘积，并找到最大的返回
    unsigned long long dfs(SumTreeNode *root, unsigned long long total) {
        if (root == nullptr) return 0;
        // 当前节点，断开左 or 右
        unsigned long long ans = 0;
        if (root->left != nullptr)
            ans = std::max(ans, (root->left->sum) * (total - root->left->sum));
        if (root->right != nullptr)
            ans =
                std::max(ans, (root->right->sum) * (total - root->right->sum));
        // 向前继续
        ans = std::max(ans, dfs(root->left, total));
        ans = std::max(ans, dfs(root->right, total));
        return ans;
    }

    int maxProduct(TreeNode *root) {
        auto sum_root = BuildSumTree(root);
        return dfs(sum_root, sum_root->sum) % 1000000007;
    }
};
