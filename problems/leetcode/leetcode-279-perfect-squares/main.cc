#include <algorithm>
#include <cstring>
using namespace std;

const int K = 100 + 5;
const int M = 10000 + 5;
int f[M];
int v[K];  // 体积数组

class Solution {
   public:
    int numSquares(int m) {
        // 预处理体积数组, 最多到 sqrt(m)
        int k = 1;
        while (1) {
            int s = k * k;
            if (s > m) break;
            v[k++] = s;
        }

        // 代入完全背包
        memset(f, 0x3f, sizeof f);
        f[0] = 0;

        for (int i = 1; i < k; i++) {
            for (int j = v[i]; j <= m; j++) {
                f[j] = min(f[j], f[j - v[i]] + 1);
            }
        }
        return f[m];
    }
};
