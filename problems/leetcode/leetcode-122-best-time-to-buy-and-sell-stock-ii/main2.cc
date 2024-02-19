#include <algorithm>
#include <vector>
using namespace std;
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // f[0] 表示手持现金, f[1] 表示手持股票
        int f[2] = {0, -prices[0]};

        for (int i = 1; i < n; i++) {
            // 持有股票, 决定卖出 or 不管
            f[0] = max(f[0], f[1] + prices[i]);
            // 持有现金, 决定买入 or 不管
            f[1] = max(f[1], f[0] - prices[i]);
        }

        // 持有现金的最大利润
        return f[0];
    }
};
