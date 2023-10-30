// https://leetcode.cn/problems/maximum-binary-tree
// 654. 最大二叉树

#include <deque>
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
    // 思路:
    // 采用递减栈
    // 比栈顶小的，直接push，栈顶的右孩子设置为这个新节点
    // 比栈顶大的，删除栈中比他小的节点，留下的就是比他大的,
    // 并把当前节点的左孩子指向最后一个逼迫走的节点
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        // 单调递减栈,  栈底最大
        deque<TreeNode *> q;
        for (int i = 0; i < nums.size(); i++) {
            TreeNode *last_pop = nullptr;
            while (!q.empty() && q.back()->val < nums[i]) {
                last_pop = q.back();
                q.pop_back();
            }
            // 创建一个新节点
            auto node = new TreeNode(nums[i]);
            if (last_pop != nullptr) node->left = last_pop;
            if (!q.empty()) q.back()->right = node;
            q.push_back(node);
        }
        return q.front();
    }
};
