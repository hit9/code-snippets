struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
   public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 特例
        if (p == root || q == root) return root;
        // p q 一个空的情况, 祖先是非空的本身
        if (p == nullptr) return q;
        if (q == nullptr) return p;
        if (root == nullptr) return nullptr;
        // 确保 p 比 q 小
        if (p->val > q->val) return lowestCommonAncestor(root, q, p);
        // 最好情况: p 在左子树, q 在右子树
        if (root->val > p->val && root->val < q->val) return root;
        // 都在左子树
        if (root->val > p->val && root->val > q->val)
            return lowestCommonAncestor(root->left, p, q);
        // 都在右子树
        return lowestCommonAncestor(root->right, p, q);
    }
};
