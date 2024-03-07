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
    void dfs(TreeNode *root, int v) {
        if (root == nullptr) return;
        if (root->left != nullptr) dfs(root->left, v * 10 + root->left->val);
        if (root->right != nullptr) dfs(root->right, v * 10 + root->right->val);
        if (root->left == nullptr && root->right == nullptr) ans += v;
    }
    int sumNumbers(TreeNode *root) {
        if (!root) return 0;
        dfs(root, root->val);
        return ans;
    }
};
