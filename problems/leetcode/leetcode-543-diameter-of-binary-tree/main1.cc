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
class Solution {
   public:
    int ans = 0;
    int dfs(TreeNode *root) {
        if (root == nullptr) return 0;
        if (!root->left && !root->right) return 0;  // 单节点深度算0
        int L = dfs(root->left);
        int R = dfs(root->right);
        ans = max(ans,
                  L + R + (root->left != nullptr) + (root->right != nullptr));
        return max(L, R) + 1;
    }
    int diameterOfBinaryTree(TreeNode *root) {
        dfs(root);
        return ans;
    }
};

// 注释
//
//   [root]
//   /   \
//  L     R
//
// 深度:单节点算0
// 那么经过 root 的最大直经是 L + R + left?1:0 + right?1:0
// 遍历所有节点作为 root, 取 max 就是整个树的最大直径
