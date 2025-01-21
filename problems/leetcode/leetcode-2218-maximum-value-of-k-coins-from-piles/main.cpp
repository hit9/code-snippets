#include <algorithm>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/maximum-value-of-k-coins-from-piles/solutions/3054067/dp-san-ceng-xun-huan-by-chao-wang-7-qy05/

class Solution {
   public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        // 考虑不断加入每个栈的方式划分阶段
        // 设 dp[x][y]  已经考虑前 x 个栈的时候, 恰好 y 次操作的时候的答案,
        // 其中 0 <= x <= n,  0 <= y <= k.
        // 初始第一行全部为 0: dp[0][0 to k] = 0. 因为没有栈
        // 初始第一列全部为 0: dp[0 to n][0] = 0. 因为操作0次
        // 目标是 dp[n][k] .
        // 接下来尝试 DP 转移:
        // 放入第 x 个栈时, 依次尝试取这个新栈的前 j 个数字, 考虑其中最大值
        // for y from 0 to k:
        //   for j from 1 to min(y, piles.depth):
        //     s = sum[1..j] # 可以前缀和优化
        //     dp[x][y] = max(dp[x-1][y-j]) + s

        int n = piles.size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        for (int x = 1; x <= n; ++x) {      // 放入第 x 个栈, x 从 1 开始
            int d = piles[x - 1].size();    // 这个栈的深度
            for (int y = 1; y <= k; ++y) {  // 考虑恰好 y 次操作时, y 从 1 开始
                int s = 0;                  // 临时记录前缀和 piles[x][0..j-1]

                // 连续取出 j 个栈顶元素, j 从 0 开始 (此时什么也不取)
                for (int j = 0; j <= min(y, d); ++j) {
                    if (j) s += piles[x - 1][j - 1];
                    // 要考虑没有考虑当前栈的时候, 恰好 y-j
                    // 次操作时可以取得的最大值 + 一个正的 s.
                    // 就可以推导当前阶段恰好操作 y 次的时候的情况,
                    // 其中最大者就是 dp[x][y]
                    dp[x][y] = max(dp[x][y], dp[x - 1][y - j] + s);
                }
            }
        }

        return dp[n][k];
    }
};
