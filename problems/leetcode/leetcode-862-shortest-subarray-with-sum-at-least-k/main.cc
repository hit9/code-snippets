// https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k
// 862. 和至少为 K 的最短子数组
// 给你一个整数数组 nums 和一个整数 k ，找出 nums 中和至少为 k 的 最短非空子数组
// ，并返回该子数组的长度。如果不存在这样的 子数组 ，返回 -1 。 子数组 是数组中
// 连续 的一部分。

#include <deque>
#include <vector>
using namespace std;
class Solution {
   public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();

        // 先求前缀和, 第一项是 0
        vector<long> sums(n + 1, 0);
        for (int i = 1; i < n + 1; i++) sums[i] = sums[i - 1] + nums[i - 1];

        // 递增队列, 队列左端留住最小的
        deque<int> q;

        int ans = n + 1;

        for (int i = 0; i < n + 1; i++) {
            // 最左端是最小的，满足条件则计算 pop 出
            while (!q.empty() && sums[i] >= sums[q.front()] + k) {
                ans = std::min(ans, i - q.front());
                q.pop_front();
            }
            // 右侧弹出更大的, 留住更小的
            while (!q.empty() && sums[q.back()] >= sums[i]) q.pop_back();
            // 右侧入队
            q.push_back(i);
        }
        return ans > n ? -1 : ans;
    }
};
