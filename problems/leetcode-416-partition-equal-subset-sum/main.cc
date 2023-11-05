// https://leetcode.cn/problems/partition-equal-subset-sum
//
// 416. 分割等和子集
// 给你一个 只包含正整数 的 非空 数组 nums
// 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
//
// 示例 1： 输入：nums = [1,5,11,5] 输出：true 解释：数组可以分割成 [1, 5, 5] 和
// [11] 。
//
// 示例 2： 输入：nums = [1,2,3,5] 输出：false
// 解释：数组不能分割成两个元素和相等的子集。

#include <numeric>
#include <vector>
using namespace std;

// 思路: 转换为01背包问题

class Solution {
   public:
    bool canPartition(vector<int>& nums) {
        int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total & 1) return false;  // 奇数不行
        int target = total / 2;

        int n = nums.size();

        // dp[i][j] = true 表示 [0...i] 内的元素，恰好可以选出来和等于 j 的子集
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

        // 初始情况
        if (nums[0] <= target) dp[0][nums[0]] = true;

        // 递推分情况讨论:
        //
        // 选择 nums[i]: 如果 [0,i-1] 区间上已经有 k 使得 dp[k][j] = true, 那么
        // dp[i][j] = true , 也就是说，如果 dp[i-1][j] = true, 则 dp[i][j] 等于
        // true
        // 选择 nums[i] 的时候，还有一种情况, 就是 nums[i] 恰好等于 j 的时候,
        // dp[i][j] = true;
        //
        // 不选择 nums[i]: 如果 [0,i-1] 区间上有恰好等于 j-nums[i] 的和，
        // 即如果 dp[i-1][j-nums[i]] = true, 那么 dp[i][j] = true;
        //
        // 三种情况取 或。
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= target; j++) {
                // [0..i-1] 上恰好有和等于 j 的情况 OR
                // nums[i] 恰好等于 j 的情况 OR
                // [0..i-1] 上有恰好等于 j - nums[i] 的情况 (注意 j 要 >
                // nums[i])
                dp[i][j] = dp[i - 1][j] || (nums[i] == j) ||
                           (j > nums[i] && dp[i - 1][j - nums[i]]);
            }
        }

        return dp[n - 1][target];
    }
};
