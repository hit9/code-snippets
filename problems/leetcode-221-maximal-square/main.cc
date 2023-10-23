
// https://leetcode.cn/problems/maximal-square

#include <iostream>
#include <vector>
using namespace std;
class Solution {
   public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int maxlen = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0)
                        dp[i][j] = 1;
                    else
                        dp[i][j] = std::min({dp[i - 1][j], dp[i][j - 1],
                                             dp[i - 1][j - 1]}) +
                                   1;
                    if (dp[i][j] > maxlen) maxlen = dp[i][j];
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        return maxlen * maxlen;
    }
};

int main(void) {
    Solution solution;
    vector<vector<char>> matrix{{'0', '1'}};
    cout << solution.maximalSquare(matrix) << endl;
    return 0;
}
