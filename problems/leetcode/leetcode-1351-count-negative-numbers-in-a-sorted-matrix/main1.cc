#include <vector>

using namespace std;

// 方法1：每行进行二分 O(mlogn)
class Solution {
   public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;
        for (int i = 0; i < m; i++) {
            // 二分查找非递减数组中 <= 0 的位置
            int l = 0;
            int r = n;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (grid[i][mid] >= 0)
                    l = mid + 1;
                else
                    r = mid;
            }
            count += n - l;
        }
        return count;
    }
};
