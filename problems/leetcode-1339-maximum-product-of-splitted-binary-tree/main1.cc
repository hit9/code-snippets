// https://leetcode.cn/problems/maximum-product-of-splitted-binary-tree
// 1339. 分裂二叉树的最大乘积
//
// 给你一棵二叉树，它的根为 root 。请你删除 1
// 条边，使二叉树分裂成两棵子树，且它们子树和的乘积尽可能大。
// 由于答案可能会很大，请你将结果对 10^9 + 7 取模后再返回。

// 思路:
// 数学hint: x + y = 固定值时，x*y 最大值在 abs(x-y) 最小时. 就是说
// 两个部分越接近, 乘积越大越大
//
// 所以，建立求和树，找到最接近  total/2 的就行了

#include <algorithm>
#include <cmath>

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

struct SumTreeNode {
    long long sum;
    SumTreeNode *left;
    SumTreeNode *right;
    SumTreeNode(long long x, SumTreeNode *left, SumTreeNode *right)
        : sum(x), left(left), right(right) {}
};

class Solution {
   public:
    // 建一个求和树，结构和原来的树一样, 每个节点的值是以其为根节点的树的总和
    SumTreeNode *BuildSumTree(TreeNode *root) {
        if (root == nullptr) return nullptr;
        auto left = BuildSumTree(root->left);
        auto right = BuildSumTree(root->right);
        long long sum = root->val;
        if (left != nullptr) sum += left->sum;
        if (right != nullptr) sum += right->sum;
        return new SumTreeNode(sum, left, right);
    }

    // 在 root 内找最最接近 half=total/2 的节点返回
    SumTreeNode *find(SumTreeNode *root, long long half) {
        if (root == nullptr) return nullptr;
        auto ans = root;
        auto l = find(root->left, half);
        auto r = find(root->right, half);
        if (l != nullptr)
            if (abs(half - ans->sum) > abs(half - l->sum)) ans = l;
        if (r != nullptr)
            if (abs(half - ans->sum) > abs(half - r->sum)) ans = r;
        return ans;
    }

    int maxProduct(TreeNode *root) {
        auto sum_root = BuildSumTree(root);
        auto total = sum_root->sum;
        auto x = find(sum_root, total / 2);
        return (x->sum * (total - x->sum)) % 1000000007;
    }
};
