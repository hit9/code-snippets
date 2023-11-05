// https://leetcode.cn/problems/greatest-sum-divisible-by-three
// 1262. 可被三整除的最大和
// 给你一个整数数组 nums，请你找出并返回能被三整除的元素最大和。
//
// 示例 1：
// 输入：nums = [3,6,5,1,8]
// 输出：18
// 解释：选出数字 3, 6, 1 和 8，它们的和是 18（可被 3 整除的最大和）。
//
// 示例 2：
//
// 输入：nums = [4]
// 输出：0
// 解释：4 不能被 3 整除，所以无法选出数字，返回 0。
//
// 示例 3：
//
// 输入：nums = [1,2,3,4,4]
// 输出：12
// 解释：选出数字 1, 3, 4 以及 4，它们的和是 12（可被 3 整除的最大和）。
//
// 提示：
// 1 <= nums[i] <= 10^4

#include <vector>

using namespace std;

// 思路:
// 动态规划
//
//  nums => [3,6,5,1,8]
//
// R               {  0,  0,  0 }
// nums[i]=3       {  3,  0,  0 }
// nums[i]=6       {  9,  0,  0 }
// nums[i]=5       {  9,  0, 14 }
// nums[i]=1       { 15, 10, 14 }
// nums[i]=8       { 18, 22, 23 }
//
// Answer: R[0] => 18
//
class Solution {
   public:
    int maxSumDivThree(vector<int>& nums) {
        // 跟进余数为 0,1,2 的最大和的值
        int R[3] = {0, 0, 0};

        for (auto num : nums) {
            // A, B, C 为考虑选择 num 的情况下的值
            int A = R[0] + num;
            int B = R[1] + num;
            int C = R[2] + num;

            // 更新对应槽位的值, 如果更大，才更新
            R[A % 3] = std::max(A, R[A % 3]);
            R[B % 3] = std::max(B, R[B % 3]);
            R[C % 3] = std::max(C, R[C % 3]);
        }

        return R[0];
    }
};
