#include <vector>
using namespace std;
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        // f[0] 手持现金, 昨日存在卖出; 不可以买, 处于冷冻期
        // f[1] 手持现金, 昨日没有卖出; 可以买
        // f[2] 手里持有股票
        int f[3];
        f[2] = -prices[0];  // 第一天买入的话,盈利是负的
        for (int i = 1; i < prices.size(); i++) {
            // 注意顺序, f[0] 卖出要放在最后转移
            // 今天卖出后,收益计入 f[0], 次日解除冷冻,再过一天就可以买了
            f[2] = max(f[2], f[1] - prices[i]);  // 不买or买入
            f[1] = max(f[1], f[0]);  // 前面没有冷冻的 or 解除冷冻
            f[0] = f[2] + prices[i];  // 卖出后转入冷冻期, 不需要 max f[0],
                                      // 因为冷冻期不能持续
        }
        return max({0, f[0], f[1]});
    }
};
