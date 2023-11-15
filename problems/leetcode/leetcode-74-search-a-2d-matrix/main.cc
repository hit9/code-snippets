// https://leetcode.cn/problems/search-a-2d-matrix/description/?envType=study-plan-v2&envId=top-100-liked
// 74. 搜索二维矩阵
// 给你一个满足下述两条属性的 m x n 整数矩阵：
//    每行中的整数从左到右按非严格递增顺序排列。
//    每行的第一个整数大于前一行的最后一个整数。
// 给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。

#include <vector>
using namespace std;
class Solution {
   public:
    // 二分查找 行
    int searchM(vector<vector<int>>& matrix, int target) {
        int M = matrix.size();     // 行数
        if (M == 0) return -1;     // 空矩阵
        int N = matrix[0].size();  // 列数

        int L = 0;
        int H = M - 1;
        int m = -1;

        // 先二分法确定行, target 只能在一行中出现
        while (L <= H) {
            m = (H + L) / 2;

            if (matrix[m][0] <= target && matrix[m][N - 1] >= target) {
                // 正好在 m 行
                return m;
            }
            if (matrix[m][0] > target) {
                // 在中间行的下方
                H = m - 1;
            } else if (matrix[m][0] < target) {
                // 在中间行的上方
                L = m + 1;
            }
        }
        return -1;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = searchM(matrix, target);
        if (m < 0) return false;

        // 在第 m 行查找 注意非严格上升
        int k;
        int L = 0;
        int H = matrix[m].size() - 1;

        while (L <= H) {
            k = (L + H) / 2;
            if (matrix[m][k] < target) {
                L = k + 1;
            } else if (matrix[m][k] > target) {
                H = k - 1;
            } else {
                return true;
            }
        }

        return false;
    }
};
int main(void) { return 0; }
