// https://leetcode.cn/problems/sliding-window-maximum/description/?envType=study-plan-v2&envId=top-100-liked
// 239. 滑动窗口最大值
// 给你一个整数数组 nums，有一个大小为 k
// 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k
// 个数字。滑动窗口每次只向右移动一位。 返回 滑动窗口中的最大值 。
//
// 示例 1：
// 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
// 输出：[3,3,5,5,6,7]
// 解释：
// 滑动窗口的位置                最大值
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7

#include <deque>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;
        deque<int> q;  // 单调递减队列，存储元素下标

        for (int i = 0; i < nums.size(); i++) {
            // 维护队尾
            while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
            q.push_back(i);
            // 维护队头
            while (!q.empty() && q.front() + k <= i) q.pop_front();
            // 取队头为最大值
            if (i >= k - 1) ans.push_back(nums[q.front()]);
        }

        return ans;
    }
};
