#include <algorithm>
#include <vector>
using namespace std;
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // f[i][j] 第 i 天获取的利润 j=0 持有现金, j=1 持有股票
        vector<vector<int>> f(n, vector<int>(2, 0));
        f[0][0] = 0;
        f[0][1] = -prices[0];

        for (int i = 1; i < n; i++) {
            // 持有股票, 决定卖出 or 不管
            f[i][0] = max(f[i - 1][1] + prices[i], f[i - 1][0]);
            // 持有现金, 决定买入 or 不管
            f[i][1] = max(f[i - 1][0] - prices[i], f[i - 1][1]);
        }

        // 持有现金的最大利润
        return f[n - 1][0];
    }
};
