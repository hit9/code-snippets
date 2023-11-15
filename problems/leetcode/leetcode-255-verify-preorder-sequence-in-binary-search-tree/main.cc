// https://leetcode.cn/problems/verify-preorder-sequence-in-binary-search-tree
// 255. 验证前序遍历序列二叉搜索树
// 给定一个 无重复元素 的整数数组 preorder ， 如果它是以二叉搜索树的先序遍历排列 ，返回 true 。
//
// 输入: preorder = [5,2,1,3,6] 输出: true
//
// 输入: preorder = [5,2,6,1,3] 输出: false

#include <stack>
#include <vector>
using namespace std;

class Solution {
   public:
    // 二叉树的前序遍历: 首先访问 根节点, 然后遍历左子树，最后遍历右子树
    // 二叉搜索树的定义：对于当前 根节点，左子树都比他小，右子树的都比他大
    // 所以先序遍历，会先沿向下递减，回溯后回头向上递增
    //
    // 局部递减，总体递增
    //
    // [5,2,1,3,6]
    // 维护一个单调递减栈
    // 根 -> 左 -> 左 -> ... 的先序过程，是栈内 push 过程 (自顶向下)
    // 最底的一个左 -> 右 -> 右 的先序过程，是栈的 pop 过程, pop 出来的是
    // **已识别到的二叉搜索子树的根节点** (自底向上)
    //
    // 先序遍历中，后面遍历的节点，一定会比最近识别的根节点的数值大,
    // 因为后面的更靠右。
    bool verifyPreorder(vector<int>& preorder) {
        stack<int> q;
        int prev = INT_MIN;
        for (int i = 0; i < preorder.size(); i++) {
            if (preorder[i] < prev) return false;
            while (!q.empty() && q.top() < preorder[i]) {
                prev = q.top();
                q.pop();
            }
            q.push(preorder[i]);
        }
        return true;
    }
};
