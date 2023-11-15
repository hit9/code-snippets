// https://leetcode.cn/problems/search-insert-position
// 35. 搜索插入位置
// 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
// 示例 1: 输入: nums = [1,3,5,6], target = 5 输出: 2

#include <vector>
using namespace std;
class Solution {
    // left左边的值一直保持小于target，
    // right右边的值一直保持大于等于target，
    // 而且left最终一定等于right+1，这么一来，
    // 循环结束后，在left和right之间画一条竖线，
    // 恰好可以把数组分为两部分：left左边的部分和right右边的部分，
    // 而且left左边的部分全部小于target，并以right结尾；
    // right右边的部分全部大于等于target，并以left为首。所以最终答案一定在left的位置。
   public:
    int searchInsert(vector<int>& nums, int target) {
        // L 左侧元素始终保持 <= target
        // R 右侧元素始终保持 >= target
        // 终止循环时越界: L = R+1
        // L 是最接近 target 的 < target 的一个左界.
        int L = 0;
        int R = nums.size() - 1;

        while (L <= R) {
            int M = L + (R - L) / 2;
            if (target == nums[M])
                return M;
            else if (target < nums[M]) {
                R = M - 1;
            } else {  // target > nums[M]
                L = M + 1;
            }
        }
        return L;
    }
};
