#include <vector>
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
    vector<int> v;
    // 中序是有序的
    void dfs(TreeNode *root, int k) {
        if (v.size() >= k) return;  // 及时剪枝
        if (root == nullptr) return;
        dfs(root->left, k);
        v.push_back(root->val);
        dfs(root->right, k);
    }
    int kthSmallest(TreeNode *root, int k) {
        if (root == nullptr) return 0;
        dfs(root,k);
        return v[k - 1];
    }
};
