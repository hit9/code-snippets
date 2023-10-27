// https://leetcode.cn/problems/maximum-width-of-binary-tree/
// 662. 二叉树最大宽度

// 思路: 层序遍历，带上 index
// 图:
// https://writings.sh/assets/images/posts/data-structure-heap-and-common-problems/heap-array-representation-3.jpeg
#include <deque>
#include <utility>
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
    int widthOfBinaryTree(TreeNode *root) {
        if (root == nullptr) return 0;
        // (Node, index)
        deque<std::pair<TreeNode *, unsigned long long>> q;
        q.push_back({root, 0});

        unsigned long long ans = 1;

        while (!q.empty()) {
            int n = q.size();
            while (n-- > 0) {
                auto [node, index] = q.front();
                q.pop_front();

                if (node == nullptr) continue;
                if (node->left != nullptr)
                    q.push_back({node->left, index * 2 + 1});
                if (node->right != nullptr)
                    q.push_back({node->right, index * 2 + 2});
            }

            if (!q.empty()) {
                auto left = q.front().second;
                auto right = q.back().second;
                ans = std::max(ans, right - left + 1);
            }
        }
        return static_cast<int>(ans);
    }
};
