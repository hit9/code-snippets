#include <algorithm>
using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
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
    // 求深度
    int D(TreeNode *root) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr) return 0;
        return std::max(D(root->left), D(root->right)) + 1;
    }
    int diameterOfBinaryTree(TreeNode *root) {
        if (root == nullptr) return 0;
        // 三种情况: 从顶点过，在左子树中、在右子树，取 max 即可
        return std::max(D(root->left) + D(root->right) +
                            (root->left != nullptr ? 1 : 0) +
                            (root->right != nullptr ? 1 : 0),
                        std::max(diameterOfBinaryTree(root->left),
                                 diameterOfBinaryTree(root->right)));
    }
};
