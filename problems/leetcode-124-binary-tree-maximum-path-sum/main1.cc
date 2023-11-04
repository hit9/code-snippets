// https://leetcode.cn/problems/binary-tree-maximum-path-sum/
// 124. 二叉树中的最大路径和
// 二叉树中的 路径
// 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中
// 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。 路径和
// 是路径中各节点值的总和。 给你一个二叉树的根节点 root ，返回其 最大路径和 。
//
// 输入：root = [1,2,3] 输出：6 解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 +
// 3 = 6
//
// 输入：root = [-10,9,20,null,null,15,7] 输出：42 解释：最优路径是 15 -> 20 ->
// 7 ，路径和为 15 + 20 + 7 = 42

#include <algorithm>
#include <utility>
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
    //  dfs 返回树 root 下的:
    //  第一项 S1 是 以 root 为结尾的路径的最大长度
    //  第二项 S2 是答案，树 root 下的最大路径和，遍历每个节点取 max
    pair<int, int> dfs(TreeNode *root) {
        if (root == nullptr) return {0, INT_MIN};

        // 递归左右子树
        auto [L1, L2] = dfs(root->left);
        auto [R1, R2] = dfs(root->right);

        // 左右子树的 > 0 的才加上，都存在时取二者最大
        auto S1 = root->val + std::max({L1, R1, 0});

        // 左右子树，只有存在且 > 0 才加上
        auto S2 = root->val;
        if (root->left != nullptr && L1 > 0) S2 += L1;
        if (root->right != nullptr && R1 > 0) S2 += R1;

        // 经过 root、不经过 root 在左子树、不经过 root 在右子树
        // 取 max
        S2 = std::max({S2, L2, R2});

        return {S1, S2};
    }

    int maxPathSum(TreeNode *root) {
        auto [_, ans] = dfs(root);
        return ans;
    }
};
