#include <vector>
using namespace std;

class Solution {
   public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ans;
        int L = 0;

        for (int k = 1; k < n - 1; k++) {  // 枚举中间的 k
            int R = n - 1;
            if (k >= 2 && nums[k] == nums[k - 1]) {
                // 如果重复枚举 k 了, 不必回溯 L, 否则重复枚举了 (L,k)
                // 同时确保 L 不重复之前枚举过的最大值 nums[L-1]
                while (L > 0 && L < k && nums[L] == nums[L - 1]) L++;
            } else
                L = 0;

            while (L < k && k < R) {
                int s = nums[L] + nums[R] + nums[k];
                if (s == 0) {
                    // 跳过重复值
                    if (!(L > 0 && nums[L] == nums[L - 1]))
                        ans.push_back({nums[L], nums[k], nums[R]});
                    L++;
                    R--;
                } else if (s < 0)  // 小了
                    L++;
                else  // 大了
                    R--;
            }
        }
        return ans;
    }
};
