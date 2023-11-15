// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii
//
// 122. 买卖股票的最佳时机 II
// 给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
// 在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股
// 股票。你也可以先购买，然后在 同一天 出售。 返回 你能获得的 最大 利润 。

#include <vector>
using namespace std;
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        // 防止 [1,2,3,4,5] 这种一路递增的情况，归一到：跌落时才卖的逻辑
        prices.push_back(INT_MIN);

        int n = prices.size();

        int L = 0;  //  买入点
        int R = 1;  //  卖出点
        int ans = 0;

        while (R < n) {
            if (prices[R - 1] > prices[R]) {
                // 价格跌落, 则应该在 R-1 处卖出
                ans += prices[R - 1] - prices[L];
                // L 最早从 R 处开始买入
                L = R;
            }
            R++;
        }

        return ans;
    }
};
