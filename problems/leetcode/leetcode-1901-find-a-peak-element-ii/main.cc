#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m = mat.size();  // 行数
        // 二分枚举行
        int l = 0, r = m - 1;
        while (l <= r) {  // 因为两边l,r都会收缩，所以，这里要 l <= r
            int i = (l + r) >> 1;
            // 先保证行内满足峰值
            int j = max_element(mat[i].begin(), mat[i].end()) - mat[i].begin();
            if (i >= 1 && mat[i][j] <= mat[i - 1][j]) {
                // 当前行更小，要排除
                // 上面的行更大, 上面必有峰
                r = i - 1;
                continue;
            }
            if (i + 1 < m && mat[i][j] <= mat[i + 1][j]) {
                l = i + 1;
                continue;
            }
            return {i, j};
        }
        return {0, 0};
    }
};
