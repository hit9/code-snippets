#include <vector>
#include <algorithm>
#include <numeric>
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
class Solution {
   public:
       vector<int> a;
       void  dfs(TreeNode* root) {
            if (root == nullptr) return;
            dfs(root->left);
            a.push_back(root->val);
            dfs(root->right);
       }
    int rangeSumBST(TreeNode *root, int low, int high) {
        dfs(root);
        auto x = lower_bound(a.begin(), a.end(), low);
        auto y = upper_bound(a.begin(), a.end(), high);
        return accumulate(x, y, 0);
    }
};
