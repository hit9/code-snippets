// https://leetcode.cn/problems/kth-smallest-element-in-a-sorted-matrix

#include <vector>

using namespace std;

// 二分判定值域

class Solution {
   public:
    // 计算矩阵中不超过指定值的元素数量
    int count(const vector<vector<int>>& matrix, int val) {
        int c = 0;
        // 从右上角开始检索
        int i = 0;                     // 行
        int j = matrix[0].size() - 1;  // 列

        // 右上角的性质: 当前行中最大、当前列中最小
        while (i < matrix.size() && j >= 0) {
            if (val >= matrix[i][j]) {
                i++;
                c += j + 1;  // 当前扫描点左边的元素都符合
            } else {
                // matrix[i][j] 严格大于 val
                j--;
            }
        }
        return c;
    }

    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();

        // 找 count(x) >= k 的下界
        int l = matrix[0][0];
        int r = matrix[m - 1][n - 1];
        while (l < r) {
            int x = (l + r) >> 1;
            if (count(matrix, x) >= k)
                r = x;
            else
                l = x + 1;
        }
        return l;
    }
};
