// https://leetcode.cn/problems/3sum
// 15. 三数之和


#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ans;

        for (int left = 0; left < n - 2; left++) {
            if (left > 0 && nums[left - 1] == nums[left]) continue;

            for (int right = n - 1; right > left + 1; right--) {
                if (right < n - 1 && nums[right + 1] == nums[right]) continue;
                auto k = 0 - nums[left] - nums[right];
                if (binary_search(nums.begin() + left + 1, nums.begin() + right,
                                  k)) {
                    ans.push_back({nums[left], k, nums[right]});
                }
            }
        }
        return ans;
    }
};
