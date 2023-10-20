// https://leetcode.cn/problems/next-permutation/description/
#include <vector>
using namespace std;

class Solution {
   public:
    void nextPermutation(vector<int>& nums) {
        // 思路, 例如 1244321
        // 从右向左找到第一处严格下降的位置 1244321
        //                                   ^
        // 反转右侧的元素                   1212344
        // 从右侧元素中找到第一个               ^
        // 比当前元素大的交换位置           1312344
        for (int i = nums.size() - 2; i >= 0; i--) {
            // 从后向前找到第一处严格下降的位置
            if (nums[i] < nums[i + 1]) {
                // 右侧 i+1..n-1 反转
                for (int j = i + 1, k = nums.size() - 1; j < k; j++, k--)
                    std::swap(nums[j], nums[k]);
                // 找到最大的一个
                for (int j = i + 1; j < nums.size(); j++) {
                    if (nums[j] > nums[i]) {
                        // 一定存在
                        std::swap(nums[i], nums[j]);
                        return;
                    }
                }
            }
        }
        // 否则，属于非严格下降序列，reverse
        for (int i = 0, j = nums.size() - 1; i < j; i++, j--) {
            std::swap(nums[i], nums[j]);
        }
    }
};
