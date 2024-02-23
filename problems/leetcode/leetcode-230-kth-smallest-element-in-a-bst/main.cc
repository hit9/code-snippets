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
    int getSize(TreeNode *root) {
        if (root == nullptr) return 0;
        return getSize(root->left) + getSize(root->right) + 1;
    }
    int kthSmallest(TreeNode *root, int k) {
        if (root == nullptr) return 0;
        int leftSize = getSize(root->left);
        if (leftSize + 1 == k) {
            return root->val;
        } else if (leftSize + 1 > k) {
            return kthSmallest(root->left, k);
        }
        return kthSmallest(root->right, k - leftSize - 1);
    }
};
