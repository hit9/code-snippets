
#include <vector>
using namespace std;

// dp 思路:
// 考虑 dp[i] 为以位置为 i 结尾的连续数组的最大和
// 如果已知 dp[i-1], 现在考虑dp[i]:
// 1. 如果 dp[i-1] >= 0, 也就是说，我们可以加上前一项的和，必然是以位置 i
// 结尾的最长的
//      也就是 dp[i] = dp[i-1] + nums[i] when dp[i-1] > 0
// 2. 如果 dp[i-1] < 0 的时候，我们就要舍弃它也就是 dp[i] = nums[i] 即可
//
// 事实上，此时也无需一个 dp 数组，只需要一个数字来递推

class Solution {
   public:
    int maxSubArray(vector<int>& nums) {
        int dp = nums[0];
        int ans = dp;

        for (int i = 1; i < nums.size(); i++) {
            if (dp >= 0)
                dp += nums[i];
            else
                dp = nums[i];
            ans = std::max(ans, dp);
        }
        return ans;
    }
};
