struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
   public:
    bool find(TreeNode* root, TreeNode* x) {
        if (root == nullptr) return false;
        if (root == x) return true;
        if (root->left != nullptr && find(root->left, x)) return true;
        if (root->right != nullptr && find(root->right, x)) return true;
        return false;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return nullptr;  // nullptr 表示找不到

        if (root == p || root == q) return root;

        if (root->left != nullptr && find(root->left, p) && find(root->left, q))
            // 都在左子树
            return lowestCommonAncestor(root->left, p, q);
        if (root->right != nullptr && find(root->right, p) &&
            find(root->right, q))
            // 都在右子树
            return lowestCommonAncestor(root->right, p, q);

        // 在两边
        return root;
    }
};
