#include <numeric>
#include <vector>
using namespace std;

// 基于 01 背包
// 因为 n 比较小 <= 30 , 所以可以采用二进制优化

const int M = (1e4 * 30) / 2 + 1;
class Solution {
   public:
    bool splitArraySameAverage(vector<int>& a) {
        int n = a.size();
        int s = accumulate(a.begin(), a.end(), 0);
        // n 是 1 时肯定不符合
        if (n == 1) return false;
        // 01 背包模型, 目标和 s/2
        int m = s / 2;
        // f[j] 的第 k 位 bit 是 1 表示拼成和 m 且花费 k 个数字可行
        int f[M];
        memset(f, 0, sizeof f);
        f[0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = m; j >= a[i]; j--) f[j] |= f[j - a[i]] << 1;
        }
        //  验证
        for (int j = 0; j <= m; j++) {
            for (int k = 1; k <= n - 1; k++) {
                if ((f[j] & 1 << k) && (j * n == s * k)) return true;
            }
        }
        return false;
    }
};
