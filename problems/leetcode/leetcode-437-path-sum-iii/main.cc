struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

using namespace std;

using ll = long long;

class Solution {
   public:
    // 求解以 root 为上端点的路径计数
    int dfs(TreeNode *root, ll s) {
        if (root == nullptr) return 0;
        // 1. 在左子树, 且长度 > 1
        // 2. 在右子树, 且长度 > 1
        // 3. 只包含 root 节点
        return dfs(root->left, s - root->val) +
               dfs(root->right, s - root->val) + (root->val == s);
    }
    // 求解 root 树内的路径数目
    int pathSum(TreeNode *root, int s) {
        ll ans = dfs(root, s);  // 以 root 为端点的
        if (root != nullptr && root->left != nullptr)
            ans += pathSum(root->left, s);  // 左子树中的
        if (root != nullptr && root->right != nullptr)
            ans += pathSum(root->right, s);  // 右子树中的
        return ans;
    }
};
