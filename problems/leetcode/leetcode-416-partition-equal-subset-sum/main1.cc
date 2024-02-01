
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canPartition(vector<int>& a) {
        int n = a.size();
        int sum = accumulate(a.begin(), a.end(), 0);
        if (sum & 1) return false;  // 奇数不行

        int m = sum / 2;
        bool dp[m + 1];
        memset(dp, 0, sizeof dp);
        dp[0] = true;

        for (int i = 1; i < n; i++) {
            for (int j = m; j >= a[i]; j--) dp[j] |= dp[j - a[i]];
        }
        return dp[m];
    }
};
