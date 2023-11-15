// https://leetcode.cn/problems/search-a-2d-matrix-ii/
//
// 编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target
// 。该矩阵具有以下特性：
// 每行的元素从左到右升序排列。
// 每列的元素从上到下升序排列。

// 思路:
// 先排除四个顶点
// 选取对角线中点 m
// 划分为四个部分, 检查 II 和  III, 再检查 I 和 IV 之一
// 减少的速度 3/4
// 时间复杂度: log4/3(m*n)  (以4/3 为底), 即 log(m*n) 的
// 在矩阵很大的时候会更快

// clang-format: off
//
//    a ----- b ----- c
//    |       |       |
//    |   I   |  II   |
//    |       |       |
//    d ----- m ----- f
//    |       |       |
//    |  III  |   IV  |
//    |       |       |
//    g ----- h ----- z
//
// clang-format: on

#include <vector>

using namespace std;

class Solution {
   public:
    bool find(vector<vector<int>>& x, int ai, int aj, int zi, int zj,
              int target) {
        if (ai > zi || aj > zj) return false;

        auto a = x[ai][aj];  // 当前矩阵最小值
        auto z = x[zi][zj];  // 当前矩阵最大值

        // 左上角和右下角相等的时候
        if (a == z) {
            if (target == a) return true;
            return false;
        }

        // 恰好在顶点
        if (target == a) return true;
        if (target == z) return true;

        // target 不在范围内的时候
        if (target < a || target > z) return false;

        // 检查顶点 c 和 g
        if (target == x[ai][zj]) return true;
        if (target == x[zi][aj]) return true;

        // 如果矩阵大小就是 4，那么直接 false
        // 这里也排除了下面的二分的死递归可能
        if (zi <= ai + 1 && zj <= aj + 1) return false;

        // 取对角线中点
        auto mi = (ai + zi) / 2;
        auto mj = (aj + zj) / 2;

        auto m = x[mi][mj];

        if (m == target) return true;

        // 检查各个子模块，每次最差排除 1/4 部分
        // 也就是说，以 3/4 的速度减少面积
        // 需要先排除 II 和 III

        // 检查 II:  b => (ai, mj), f => (mi, zj)
        // 不包含 m 所在行和列
        if (find(x, ai, mj + 1, mi - 1, zj, target)) return true;

        // 检查 III: d => (mi, aj), h => (zi, mj)
        // 不包含 m 所在行和列
        if (find(x, mi + 1, aj, zi, mj - 1, target)) return true;

        // 检查 I (包括 m 所在行和列)
        if (target < m) return find(x, ai, aj, mi, mj, target);

        // 检查 IV  (包括 m 所在行和列)
        return find(x, mi, mj, zi, zj, target);
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        return find(matrix, 0, 0, m - 1, n - 1, target);
    }
};

int main(void) {
    vector<vector<int>> matrix{{1, 4, 7, 11, 15},
                               {2, 5, 8, 12, 19},
                               {3, 6, 9, 16, 22},
                               {10, 13, 14, 17, 24},
                               {18, 21, 23, 26, 30}};
    Solution s;
    s.searchMatrix(matrix, 5);
    return 0;
}
