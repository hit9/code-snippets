#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
class Solution {
   public:
    int maxCoins(vector<int>& a) {
        int n = a.size();
        // 两边插入假气球 1, 其中 [1...n] 是真实气球
        a.insert(a.begin(), 1), a.push_back(1);

        // f[i][j] 表示开区间 (i,j) 上的答案
        // 即当前剩余的相邻两个气球 i 和 j 之间的最大收益
        // 最终答案是 区间(0,n+1) 上的 f[0][n+1], 长度是 n+1
        // 最开始, (i,i), (i, i+1) 表示都不戳破, 收益是 0
        int f[n + 2][n + 2];
        memset(f, 0, sizeof f);

        for (int len = 2; len <= n + 1; len++) {  // 阶段: 枚举区间长度
            for (int i = 0; i <= n + 1 - len; i++) {  // 区间左端, 不包含
                int j = i + len;                      // 区间右端, 不包含
                // 枚举区间分割点
                for (int k = i + 1; k < min(j, n + 1); k++) {
                    // 戳破 k 的时候带来新贡献
                    // 再联合左右子区间的贡献, 和 原来取最值
                    f[i][j] =
                        max(f[i][j], f[i][k] + f[k][j] + a[i] * a[k] * a[j]);
                }
            }
        }

        return f[0][n + 1];
    }
};
