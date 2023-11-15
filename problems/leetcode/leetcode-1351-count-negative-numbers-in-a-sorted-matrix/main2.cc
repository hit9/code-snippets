#include <vector>

using namespace std;

// 方法2：从右上角搜索 O(m+n)
// https://writings.sh/post/algorithm-search-sorted-2d-matrix

class Solution {
   public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int i = 0;
        int j = n - 1;
        int count = 0;
        // 右上角性质: 当前行最小值、当前列最大值
        while (i < m && j >= 0) {
            if (grid[i][j] < 0) {
                // 当前列此行以下的部分肯定全部 < 0
                count += m - i;
                // 排除当前列
                j--;
            } else {
                // 当前行左边的部分肯定都 >= 0
                // 排除当前行
                i++;
            }
        }
        return count;
    }
};
