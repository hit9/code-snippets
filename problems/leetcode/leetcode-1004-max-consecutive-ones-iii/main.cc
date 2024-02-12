// https://leetcode.cn/problems/max-consecutive-ones-iii
// 1004. 最大连续1的个数 III

#include <vector>
using namespace std;
class Solution {
   public:
    int longestOnes(vector<int>& nums, int k) {
        int k0 = 0;  // 当前 0 的个数
        int ans = 0;
        for (int L = 0, R = 0; R < nums.size(); R++) {
            if (nums[R] == 0) k0++;

            // L <= R 而不是 L < R，允许空窗口出现，因为 k 可能是 0
            // 空窗口的时候，答案恰好是 0
            while (L <= R && k0 > k) {
                if (nums[L++] == 0) k0--;
            }

            ans = std::max(ans, R - L + 1);
        }
        return ans;
    }
};
