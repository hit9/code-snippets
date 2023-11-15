// https://leetcode.cn/problems/coin-change
// 322. 零钱兑换
// 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount
// ，表示总金额。 计算并返回可以凑成总金额所需的 最少的硬币个数
// 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
// 你可以认为每种硬币的数量是无限的。
//
// 输入：coins = [1, 2, 5], amount = 11 输出：3 解释：11 = 5 + 5 + 1
//
// 输入：coins = [2], amount = 3 输出：-1

#include <vector>
using namespace std;
class Solution {
   public:
    int coinChange(vector<int>& coins, int S) {
        // dp[s] 表示凑数量为 s 需要的最少步数
        vector<int> dp(S + 1, S + 1);
        dp[0] = 0;
        for (int i = 1; i <= S; i++) {
            for (int j = 0; j < coins.size(); j++) {
                if (coins[j] <= i)
                    dp[i] = std::min(dp[i], dp[i - coins[j]] + 1);
            }
        }
        return dp[S] > S ? -1 : dp[S];
    }
};
