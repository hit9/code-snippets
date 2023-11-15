// https://leetcode.cn/problems/binary-tree-right-side-view/
// 199. 二叉树的右视图
// 层序遍历，每层最右一个元素

#include <queue>
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
    vector<int> rightSideView(TreeNode *root) {
        vector<int> ans;
        if (root == nullptr) return ans;

        deque<TreeNode *> q;
        q.push_back(root);

        while (!q.empty()) {
            int n = q.size();
            int v = 999;
            while (n > 0) {
                auto node = q.front();
                q.pop_front();
                n--;
                if (node == nullptr) continue;
                v = node->val;
                if (node->left != nullptr) q.push_back(node->left);
                if (node->right != nullptr) q.push_back(node->right);
            }
            if (v != 999) ans.push_back(v);
        }

        return ans;
    }
};
