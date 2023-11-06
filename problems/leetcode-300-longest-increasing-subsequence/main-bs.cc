// https://leetcode.cn/problems/longest-increasing-subsequence
//
// 300. 最长递增子序列
// 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
// 子序列
// 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7]
// 是数组 [0,3,1,6,2,2,7] 的子序列。
//
// 示例 1：
// 输入：nums = [10,9,2,5,3,7,101,18]
// 输出：4
// 解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
//
// 示例 2：
//
// 输入：nums = [0,1,0,3,2,3]
// 输出：4
//
// 示例 3：
//
// 输入：nums = [7,7,7,7,7,7,7]
// 输出：1

// 本问题的经典解法是动态规划
// 但是这里是一个二分思路
// 主要思路是，让上升子序列上升的更慢，遇到更小的元素，去把序列替换的更低
// 这样就会尽可能的长

#include <vector>

using namespace std;

class Solution {
   public:
    // 在递增数组 nums 上查找目标 x
    // right 是最右端元素位置
    // 找到恰好 >= x 的位置
    // ... a b....
    //       ^
    //       x     使得  a < x <= b
    // 等价于找到插入位置的问题
    int bs(const vector<int>& nums, int right, int x) {
        int left = 0;
        while (left <= right) {
            // 终止时，left 越过 right
            // [0..left) 始终保证严格 < x
            // (right..n-1] 始终保证严格 > x
            // 所以 left 位置就是最合适的替换位置
            int mid = left + (right - left) / 2;
            if (nums[mid] == x)
                return mid;
            else if (nums[mid] < x)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }

    int lengthOfLIS(vector<int>& nums) {
        int right = 0;  // [0..right]  追踪最长递增子序列

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[right])
                nums[++right] = nums[i];
            else {
                // 找到第一个 <= nums[i] 的位置
                int j = bs(nums, right, nums[i]);
                // 替换那个元素为更小的 nums[i]
                // 让序列上升的更慢
                nums[j] = nums[i];
            }
        }
        return right + 1;
    }
};
