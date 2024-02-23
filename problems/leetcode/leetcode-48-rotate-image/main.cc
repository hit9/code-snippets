#include <vector>
using namespace std;

class Solution {
   public:
    void rotate(vector<vector<int>>& g) {
        int n = g[0].size();
        // 从外围向内围顺时针
        for (int p = 0; 2 * p <= n; p++) {
            // 从 [p, p] 到 [p, n-1-p] 依次作为起点, 注意避开行尾
            for (int i = p, j = p; j < n - 1 - p; j++) {
                // 把元素 [i,j] 旋转 4 次
                for (int x = i, y = j, tmp = g[i][j], k = 0; k < 4; k++) {
                    int tx = y, ty = n - 1 - x;
                    std::swap(tmp, g[tx][ty]);
                    x = tx, y = ty;
                }
            }
        }
    }
};
