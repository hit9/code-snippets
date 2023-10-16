// https://leetcode.cn/problems/first-missing-positive/description/?envType=study-plan-v2&envId=top-100-liked
// 41. 缺失的第一个正数
// 给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
// 请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
//
// 示例 1： 输入：nums = [1,2,0] 输出：3
//
// 示例 2： 输入：nums = [3,4,-1,1] 输出：2
//
// 示例 3： 输入：nums = [7,8,9,11,12] 输出：1

#include <vector>
using namespace std;
class Solution {
   public:
    int firstMissingPositive(vector<int>& nums) {
        // 把 nums[i] 放到下标为 nums[i]-1 的位置上
        for (auto i = 0; i < nums.size(); i++) {
            // 虽然是 while ，不断调整
            // 但是由于每次的交换操作都会使得某一个数交换到正确的位置，
            // 因此交换的次数最多为 O(N)
            while (nums[i] > 0 && nums[i] <= nums.size() &&
                   nums[i] != nums[nums[i] - 1]) {
                // nums[i] 要符合范围
                // 如果不等于，才交换
                std::swap(nums[i], nums[nums[i] - 1]);
            }
        }
        // 找到第一个 (下标+1 != 值) 的位置
        for (auto i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) return i + 1;
        }
        return nums.size() + 1;  // [1,2,3,4] 的情况
    }
};

int main(void) { return 0; }
