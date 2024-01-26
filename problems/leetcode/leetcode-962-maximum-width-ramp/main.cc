// https://leetcode.cn/problems/maximum-width-ramp
// 962. 最大宽度坡
// 给定一个整数数组 A，坡是元组 (i, j)，其中  i < j 且 A[i] <=
// A[j]。这样的坡的宽度为 j - i。 找出 A 中的坡的最大宽度，如果不存在，返回 0 。
//
// 输入：[6,0,8,2,1,5] 输出：4 解释： 最大宽度的坡为 (i, j) = (1, 5): A[1] = 0
// 且 A[5] = 5.
//
// 输入：[9,8,1,0,1,9,4,0,4,1] 输出：7 解释： 最大宽度的坡为 (i, j) = (2, 9):
// A[2] = 1 且 A[9] = 1.

#include <stack>
#include <vector>
using namespace std;
class Solution {
   public:
    int maxWidthRamp(vector<int>& nums) {
        // 先从第 0 项，构建一个单调递减栈
        // 注意栈底保持第0项
        // 此时，最大坡的左端点一定在这个栈内
        // 这个可以反证的, 如果不在这个栈内，比如说下标 b
        // 是最大坡的左端点，不在这个栈内 那么 b 一定其左侧的某个值大。
        // 如此，b 就不可能成为最长的坡。那个左侧比 b 小的会构成一个更长的坡

        stack<int> s;
        s.push(0);
        for (int i = 1; i < nums.size(); i++)
            if (nums[s.top()] > nums[i]) s.push(i);

        // 然后就可以从右向左遍历这个数组
        // 每次都计算下可以形成的最大坡度.
        // 对于每个可能的右端点，左侧要尽可能的靠左，也就是说满足
        // 左端点值<=右端点值的情况下，左侧不断 pop
        // 因为右端向左走的，所以 pop 出去的左端不会比当前能形成更长的坡,
        // 可以勇敢pop
        int ans = 0;
        for (int i = nums.size() - 1; i >= 0; i--) {
            while (!s.empty() && nums[s.top()] <= nums[i]) {
                ans = std::max(i - s.top(), ans);
                s.pop();
            }
        }
        return ans;
    }
};
