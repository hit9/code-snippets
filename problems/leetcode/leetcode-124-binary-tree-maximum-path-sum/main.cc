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

// 思路:
// 1. 构造 dp 树，dp[node] 表示以 node 为根节点的、到 node
// 为结尾节点的路径的最大和
// 2. dfs 找最大路径和，遍历每个节点，找到经过这个节点的最大路径和.
//  ans => [ dp (left) ] + root.val + [ dp (right) ]
// 再取所有之 max
#include <algorithm>
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

// dp[i] 记录以 i 根节点的子树中，以 i 为结尾的路径的最大和
struct DpTreeNode {
    int sum;
    TreeNode *node;  // 原节点
    DpTreeNode *left;
    DpTreeNode *right;
    DpTreeNode(TreeNode *node, int sum, DpTreeNode *left, DpTreeNode *right)
        : node(node), sum(sum), left(left), right(right){};
};

class Solution {
   public:
    // 构造 Dp 树
    DpTreeNode *BuildDpTree(TreeNode *root) {
        if (root == nullptr) return nullptr;

        // 递归构造左右子树
        auto L = BuildDpTree(root->left);
        auto R = BuildDpTree(root->right);

        // 以当前节点为结尾, 必须吸收 val
        auto sum = root->val;

        // 左右子树如果任何一个存在且大于0，才吸收
        // 都存在时，取二者最大
        sum += std::max((L == nullptr) ? 0 : std::max(L->sum, 0),
                        (R == nullptr) ? 0 : std::max(R->sum, 0));

        return new DpTreeNode(root, sum, L, R);
    }

    // dfs Dp 树，找到最大路径和
    // 对于每个节点，检查其左右子树的最大 dp 路径, 串联起来:
    // [左子树 dp 值] + [root.val] + [右子树 dp 值]
    // 左右子树，都是要 > 0 才串上去
    int dfs(DpTreeNode *root) {
        if (root == nullptr) return INT_MIN;

        int ans = root->node->val;

        auto L = root->left;
        auto R = root->right;

        // 左右子树，只有存在且 > 0 才加上
        if (L != nullptr && L->sum > 0) ans += L->sum;
        if (R != nullptr && R->sum > 0) ans += R->sum;

        // 递归查找左右子树
        return std::max({ans, dfs(root->left), dfs(root->right)});
    }

    int maxPathSum(TreeNode *root) { return dfs(BuildDpTree(root)); }
};
