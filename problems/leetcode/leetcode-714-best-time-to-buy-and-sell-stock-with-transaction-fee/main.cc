// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee
// 714. 买卖股票的最佳时机含手续费
// 给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格 ；整数 fee
// 代表了交易股票的手续费用。
// 你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
// 返回获得利润的最大值。
// 注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

#include <vector>
using namespace std;
class Solution {
   public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        // dp[i][0] 表示在第 i 天不持有股票的最大获利
        // dp[i][1] 表示在第 i 天持有股票的最大获利
        vector<vector<int>> dp(n, vector<int>(2, 0));

        // 第 0 天，不持有，获利 0
        dp[0][0] = 0;
        // 第 0 天，持有，获利负的，相当于透支 prices[0]
        dp[0][1] = -prices[0];

        for (int i = 1; i < n; i++) {
            // 今天不持有的情况:
            // 1. 昨日持有、今日卖出,
            // 把价格直接作为利润，因为买入成本会被提前扣减
            // 2. 昨日也不持有
            dp[i][0] = std::max(dp[i - 1][1] + prices[i] - fee, dp[i - 1][0]);
            // 今天持有的情况
            // 1. 昨天也持有，今天不卖
            // 2. 昨天没持有，今天买入, 把成本计入利润扣减项
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }

        return dp[n - 1][0];
    }
};
