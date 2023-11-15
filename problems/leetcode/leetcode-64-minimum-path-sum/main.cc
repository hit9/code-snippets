// https://leetcode.cn/problems/minimum-path-sum
// 64. 最小路径和
// 给定一个包含非负整数的 m x n 网格 grid
// ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
// 说明：每次只能向下或者向右移动一步。
#include <vector>
using namespace std;
class Solution {
   public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0)
                    dp[i][j] = 0;
                else if (i == 0)
                    dp[i][j] = dp[i][j - 1];
                else if (j == 0)
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]);
                dp[i][j] += grid[i][j];
            }
        }
        return dp[m - 1][n - 1];
    }
};
