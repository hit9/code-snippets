// https://leetcode.cn/problems/skFtm2/
#include <vector>
using namespace std;
class Solution {
   public:
    int singleNonDuplicate(vector<int>& nums) {
        // 思路:
        // 二分查找
        // 如果左右都不等于 nums[M], 则直接返回
        // 如果左边的等于 nums[M]:
        //  左边有偶数 (包括自身) 个元素, 则向右边找
        //  左边有奇数 (包括自身) 个元素, 则向左边找
        // 同理对右边的情况

        int L = 0, R = nums.size();
        int M;

        while (L <= R) {
            M = (L + R) / 2;
            if (M > 0 && nums[M] == nums[M - 1]) {
                if ((M + 1) & 1) {
                    // 左边，包括自身，奇数个元素，则向左边找
                    R = M - 2;
                } else
                    L = M + 1;
            } else if (M < nums.size() - 1 && nums[M] == nums[M + 1]) {
                if ((nums.size() - M) & 1) {
                    // 右边，包括自身，奇数个元素，则向右边找
                    L = M + 2;
                } else
                    R = M - 1;
            } else {
                return nums[M];
            }
        }
        return 0;
    }
};
