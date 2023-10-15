// https://leetcode.cn/problems/search-in-rotated-sorted-array
// 33. 搜索旋转排序数组
// 整数数组 nums 按升序排列，数组中的值 互不相同 。
// 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了
// 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ...,
// nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3
// 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
// 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target
// ，则返回它的下标，否则返回 -1 。 你必须设计一个时间复杂度为 O(log n)
// 的算法解决此问题。 示例 1： 输入：nums = [4,5,6,7,0,1,2], target = 0 输出：4
// 示例 2： 输入：nums = [4,5,6,7,0,1,2], target = 3 输出：-1
// 示例 3： 输入：nums = [1], target = 0 输出：-1

#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int search(vector<int>& nums, int target) {
        int L = 0;
        int R = nums.size() - 1;
        int M;

        while (L <= R) {
            M = (L + R) / 2;

            if (nums[M] == target) return M;
            if (nums[L] == target) return L;
            if (nums[R] == target) return R;

            // 仅剩余一个元素 或者 两个元素时，不必要再继续判断
            if (L == R || R == L + 1) return -1;

            if (nums[L] < nums[M]) {
                // M 在第一段升序序列中
                if (nums[L] < target && target < nums[M]) {
                    // 在 M 左侧
                    R = M - 1;
                } else {
                    // 在 M 右侧
                    L = M + 1;
                }
            } else if (nums[M] < nums[R]) {
                // M 在第二段升序序列中
                if (nums[M] < target && target < nums[R]) {
                    // 在 M 右侧
                    L = M + 1;
                } else {
                    // 在 M 左侧
                    R = M - 1;
                }
            }
        }

        return -1;
    }
};

int main(void) {
    vector nums{4, 5, 6, 7, 0, 1, 2};
    Solution solution;
    cout << solution.search(nums, 0) << endl;
    return 0;
}
