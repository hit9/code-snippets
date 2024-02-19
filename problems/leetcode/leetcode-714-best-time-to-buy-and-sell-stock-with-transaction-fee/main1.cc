#include <vector>
using namespace std;
class Solution {
   public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();

        // f[0] 手持现金, f[1] 手持股票
        int f[2] = {0, -prices[0]};

        for (int i = 1; i < n; i++) {
            // 今天不持有的情况:
            // 1. 昨日持有、今日卖出,
            // 把价格直接作为利润，因为买入成本会被提前扣减
            // 2. 昨日也不持有
            f[0] = std::max(f[1] + prices[i] - fee, f[0]);
            // 今天持有的情况
            // 1. 昨天也持有，今天不卖
            // 2. 昨天没持有，今天买入, 把成本计入利润扣减项
            f[1] = std::max(f[1], f[0] - prices[i]);
        }

        return f[0];
    }
};
