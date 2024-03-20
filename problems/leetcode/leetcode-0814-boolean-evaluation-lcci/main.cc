#include <cstring>
#include <string>
using namespace std;

class Solution {
   public:
    int countEval(string s, int result) {
        int n = s.size();
        if (n == 1) return s[0] - '0' == result;  // 特判

        // f[i][j][v]  表示 区间 [i,j] 上的计算结果是 v 的方案数
        int f[n][n][2];
        memset(f, 0, sizeof f);

        for (int i = 0; i < n; i += 2) f[i][i][s[i] - '0'] = 1;

        for (int len = 1; len <= n; len += 2) {         // 枚举区间长度
            for (int i = 0; i + len - 1 < n; i += 2) {  // 枚举区间左端
                int j = i + len - 1;
                for (int k = i + 1; k < j; k += 2) {  // 枚举分割点(计算符)
                    // [i..k-1] op[k] [k+1...j]
                    int v1, v2, v3, v4;
                    switch (s[k]) {
                        case '&':
                            v1 = 0, v2 = 0, v3 = 0, v4 = 1;
                            break;
                        case '|':
                            v1 = 0, v2 = 1, v3 = 1, v4 = 1;
                            break;
                        case '^':
                            v1 = 0, v2 = 1, v3 = 1, v4 = 0;
                            break;
                    }
                    f[i][j][v1] += f[i][k - 1][0] * f[k + 1][j][0];
                    f[i][j][v2] += f[i][k - 1][1] * f[k + 1][j][0];
                    f[i][j][v3] += f[i][k - 1][0] * f[k + 1][j][1];
                    f[i][j][v4] += f[i][k - 1][1] * f[k + 1][j][1];
                }
            }
        }

        return f[0][n - 1][result];
    }
};
