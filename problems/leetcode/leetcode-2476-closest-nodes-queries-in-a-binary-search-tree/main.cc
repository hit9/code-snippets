#include <algorithm>
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
    vector<int> a;
    void dfs(TreeNode *root) {
        if (root == nullptr) return;
        dfs(root->left);
        a.push_back(root->val);
        dfs(root->right);
    }
    vector<vector<int>> closestNodes(TreeNode *root, vector<int> &queries) {
        vector<vector<int>> ans;
        dfs(root);
        for (auto q : queries) {
            auto x = upper_bound(a.begin(), a.end(), q);  // > q
            auto y = lower_bound(a.begin(), a.end(), q);  // >= q
            ans.push_back(
                {x != a.begin() ? *(x - 1) : -1, y != a.end() ? *y : -1});
        }
        return ans;
    }
};
