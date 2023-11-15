// https://leetcode.cn/problems/pascals-triangle
#include <vector>
using namespace std;
class Solution {
   public:
    vector<vector<int>> generate(int n) {
        vector<vector<int>> dp;
        dp.push_back({1});
        for (int i = 1; i < n; i++) {
            vector<int> row;
            row.push_back(1);
            for (int j = 1; j < i - 1; j++) {
                row.push_back(dp[i - 1][j] + dp[i - 1][j - 1]);
            }
            row.push_back(1);
            dp.push_back(row);
        }
        return dp;
    }
};
