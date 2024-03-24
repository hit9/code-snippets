#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int N = 101;

class Solution {
   public:
    int minScoreTriangulation(vector<int>& values) {
        // 双倍数组, 破环成两倍链
        values.insert(values.begin(), values.begin(), values.end());

        int n = values.size();

        // f[i][j] 表示顶点 [i..j] 组成的子凸多边形形成的最低得分
        int f[N][N];
        memset(f, 0x3f, sizeof f);

        // 边不算入得分
        for (int i = 0; i + 1 < n; i++) f[i][i + 1] = 0;

        // 三角形
        for (int i = 0; i + 2 < n; i++)
            f[i][i + 2] = values[i] * values[i + 1] * values[i + 2];

        for (int len = 4; len <= n / 2; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                // 枚举分割点 k, 可行的划分
                // 三角形 [i, k, j] 和多边形 [i..k], [k...j]
                for (int k = i + 1; k < j; k++) {
                    f[i][j] = min(f[i][j], values[i] * values[k] * values[j] +
                                               f[i][k] + f[k][j]);
                }
            }
        }

        // 考虑以 i 为起始点的情况的原始多边形的答案
        int ans = 0x3f3f3f3f;
        for (int i = 0; i < n / 2; i++) {
            ans = min(ans, f[i][i + n / 2 - 1]);
        }

        return ans;
    }
};
