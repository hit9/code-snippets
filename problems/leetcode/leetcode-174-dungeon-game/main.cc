#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

#define M 201
#define N 201
#define inf 0x3f3f3f3f

int f[M][N];

class Solution {
   public:
    int calculateMinimumHP(vector<vector<int>>& d) {
        int m = d.size(), n = d[0].size();

        memset(f, 0x3f, sizeof f);

        // 初始值
        f[m][n + 1] = 1, f[m + 1][n] = 1;

        // f[i][j] 的含义是到达 i,j 处所需的最少点数

        for (int i = m; i > 0; i--) {
            for (int j = n; j > 0; j--) {
                f[i][j] =
                    max(min(f[i + 1][j], f[i][j + 1]) - d[i - 1][j - 1], 1);
            }
        }

        return f[1][1];
    }
};
