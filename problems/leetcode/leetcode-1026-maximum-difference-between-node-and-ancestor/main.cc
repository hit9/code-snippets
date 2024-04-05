#include <algorithm>
#include <cstdlib>
#include <utility>

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
    int ans = 0;
    // dfs 返回子树 root 中的最大值, 最小,
    pair<int, int> dfs(TreeNode *root) {
        int ma = -1, mi = 0x3f3f3f3f;
        if (root->left != nullptr) {
            auto [mal, mil] = dfs(root->left);
            ma = max(ma, mal);
            mi = min(mi, mil);
        }
        if (root->right != nullptr) {
            auto [mar, mir] = dfs(root->right);
            ma = max(ma, mar);
            mi = min(mi, mir);
        }
        // 没有儿子的情况
        if (ma < 0 || mi >= 0x3f3f3f3f) return {root->val, root->val};
        ans = max({ans, abs(root->val - ma), abs(root->val - mi)});
        return {max(root->val, ma), min(root->val, mi)};
    }
    int maxAncestorDiff(TreeNode *root) {
        dfs(root);
        return ans;
    }
};
