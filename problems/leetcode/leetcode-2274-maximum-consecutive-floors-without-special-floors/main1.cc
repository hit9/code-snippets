#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    // dp 思路
    int maxConsecutive(int bottom, int top, vector<int>& special) {
        sort(special.begin(), special.end());
        int n = special.size();
        vector<int> dp(n, 0);
        dp[0] = special[0] - bottom;
        for (int j = 1; j < special.size(); ++j) {
            int a = special[j] - special[j - 1] - 1;
            dp[j] = max(dp[j - 1], a);
        }
        return max(dp[n - 1], top - special[n - 1]);
    }
};
