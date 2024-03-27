#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
using ll = long long;

class Solution {
   public:
    int countWays(vector<vector<int>>& ranges) {
        int n = ranges.size();
        // 先按左端点排序
        sort(ranges.begin(), ranges.end());

        // 合并区间, 得到 m 个大区间
        int m = 1;
        // L, R 表示当前连续的大区间的左右
        int L = ranges[0][0], R = ranges[0][1];

        for (auto& r : ranges) {
            if (r[0] <= R) {
                // 和当前大区间存在交叉, 更新右端
                R = max(R, r[1]);
            } else {
                // 和当前大区间无交叉, 替换当前大区间
                L = r[0], R = r[1];
                m++;
            }
        }

        // 要把所有的 m 分成两组, 有2**m 个方法
        // 需要做个快速幂
        return fastpow(2, m, MOD);
    }

    // 计算 x 的 k 次幂, 余 mod
    int fastpow(int x, int n, int mod) {
        ll a = 1;
        ll b = x;
        while (n) {
            if (n & 1) {
                a = a * b % mod;
                n--;
            } else {
                b = b * b % mod;
                n >>= 1;
            }
        }
        return a % mod;
    }
};
