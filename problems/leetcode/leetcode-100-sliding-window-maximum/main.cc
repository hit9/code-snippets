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
        vector<int> results;

        // q 单调队列：有一个性质:
        // 队列中前面的比后面的大, 比如 [3, 2, 1] 是合法的, [1,2,3] 就不行要,
        // 简化为 [3]
        deque<int> q;

        // 第一个窗口 [0, k-1] 的先入队
        for (int i = 0; i < k; i++) {
            while (!q.empty() && nums[i] > q.back()) q.pop_back();
            q.push_back(nums[i]);
        }

        // 添加第一个结果
        results.push_back(q.front());

        // 窗口移动过程中, 右侧不断入队, 左侧如果等于队头，则出队
        for (int i = 1; i + k <= nums.size(); i++) {
            // 入队 a, 出队 b
            int a = nums[i + k - 1];
            int b = nums[i - 1];

            // 注意一点, 只有队尾严格小于要入队的元素时，才会被弹出
            // 也就是说，对于重复元素，会在队列中有多份存在
            // 这样，队头弹出时也可以放心弹出，不会影响弹出后的最大值
            if (!q.empty() && q.front() == b) q.pop_front();
            while (!q.empty() && a > q.back()) q.pop_back();
            q.push_back(a);

            results.push_back(q.front());
        }

        return results;
    }
};
