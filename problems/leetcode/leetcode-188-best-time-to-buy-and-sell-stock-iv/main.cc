#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        // f[0][j] 表示进行了 j 次买入, 目前手持现金
        // f[1][j] 表示进行了 j 次买入, 目前手上有股票(最多持有一只)
        int f[2][101];
        memset(f, 0xcf, sizeof f);

        f[0][0] = 0;           // 第 0 天不买入的话, 获利 0
        f[1][1] = -prices[0];  // 第 0 天买入的话

        for (int i = 1; i < prices.size(); i++) {  // 从第一天开始算
            for (int j = 1; j <= k; j++) {
                // 手上有股票 => 现金状态
                // 不卖 or 卖
                f[0][j] = max(f[0][j], f[1][j] + prices[i]);
                // 手上有现金 => 有股票状态
                // 不买 or 买(注意买的时候会增加交易次数)
                f[1][j] = max(f[1][j], f[0][j - 1] - prices[i]);
            }
        }
        // max of f[0]
        return max(0, *max_element(begin(f[0]), end(f[0])));
    }
};
