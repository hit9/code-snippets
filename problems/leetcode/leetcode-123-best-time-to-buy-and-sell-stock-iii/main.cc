#include <vector>
using namespace std;
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        // f[j][0] 表示进行了 k 次买入, 目前手持现金
        // f[j][1] 表示进行了 k 次买入, 目前手上有股票(最多持有一只)
        int f[3][2];
        memset(f, 0xcf, sizeof f);

        f[0][0] = 0;           // 第 0 天不买入的话, 获利 0
        f[1][1] = -prices[0];  // 第 0 天买入的话

        for (int i = 1; i < prices.size(); i++) {  // 从第一天开始算
            for (int j = 1; j <= 2; j++) {
                // 手上有股票 => 现金状态
                // 不卖 or 卖
                f[j][0] = max(f[j][0], f[j][1] + prices[i]);
                // 手上有现金 => 有股票状态
                // 不买 or 买(注意买的时候会增加交易次数)
                f[j][1] = max(f[j][1], f[j - 1][0] - prices[i]);
            }
        }
        // max of f[j][0]
        return max({0, f[1][0], f[2][0]});
    }
};
