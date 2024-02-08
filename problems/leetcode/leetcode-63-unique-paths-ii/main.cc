#include <vector>
using namespace std;

const int M = 101, N = 101;

class Solution {
   public:
    int uniquePathsWithObstacles(vector<vector<int>>& g) {
        if (g[0][0]) return 0;
        int m = g.size(), n = g[0].size();
        int f[M][N];
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j]) continue;
                if (i > 0 && g[i - 1][j] == 0) f[i][j] += f[i - 1][j];
                if (j > 0 && g[i][j - 1] == 0) f[i][j] += f[i][j - 1];
            }
        }
        return f[m - 1][n - 1];
    }
};
