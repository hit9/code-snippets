// https://leetcode.cn/problems/maximum-product-subarray/
// 152. 乘积最大子数组
// 给你一个整数数组 nums
// ，请你找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
// 测试用例的答案是一个 32-位 整数。
// 子数组 是数组的连续子序列。
//
// 输入: nums = [2,3,-2,4] 输出: 6 解释: 子数组 [2,3] 有最大乘积 6。
//
// 输入: nums = [-2,0,-1] 输出: 0 解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

#include <vector>
using namespace std;

class Solution {
   public:
    int calc(vector<int>& nums) {
        long long x = nums[0];
        long long ans = x;
        for (int i = 1; i < nums.size(); i++) {
            x = x ? x * nums[i] : nums[i];
            ans = std::max({ans, x, static_cast<long long>(nums[i])});
        }
        return ans;
    }
    int maxProduct(vector<int>& nums) {
        auto m1 = calc(nums);
        std::reverse(nums.begin(), nums.end());
        auto m2 = calc(nums);
        // 正反向扫描取最大
        // 防止类似: [2,-5,-2,-4,3] 的case，其最大乘积更靠右是 23
        // 如果只从左边扫，就是 20
        return std::max(m1, m2);
    }
};
