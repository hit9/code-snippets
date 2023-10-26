// https://leetcode.cn/problems/max-consecutive-ones-iii
// 1004. 最大连续1的个数 III


#include <vector>
using namespace std;
class Solution {
   public:
    int longestOnes(vector<int>& nums, int k) {
        int k0 = 0;  // 当前 0 的个数
        int ans = 0;
        for (int left = 0, right = 0; right < nums.size(); right++) {
            if (nums[right] == 0) k0++;

            while (k0 > k && left <= right) {
                if (nums[left] == 0) k0--;
                left++;
            }

            ans = std::max(ans, right - left + 1);
        }
        return ans;
    }
};
