#include <numeric>
#include <vector>
using namespace std;
// 一个很好的测试用例: [5,3,11,19,2], 总和是 40
// 分割方案: [5,11] 和 [3,19,2], 平均数是 8
// 注意: s 可以不是偶数, 分割后的数组也不一定是大小相等的
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
        // 拼成和 m 且花费 k 个数字是否可行
        bool f[M][30];
        memset(f, 0, sizeof f);
        f[0][0] = true;
        for (int i = 0; i < n; i++) {
            for (int j = m; j >= a[i]; j--)
                for (int k = 1; k <= n - 1; k++) {
                    f[j][k] |= f[j - a[i]][k - 1];
                    // 验证
                    if (f[j][k] && (j * n == s * k)) return true;
                }
        }
        return false;
    }
};
