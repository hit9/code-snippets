#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <vector>
using namespace std;

class Solution1 {
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

class Solution2 {
   public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = 0, j = matrix[0].size() - 1;
        while (i < matrix.size() && j >= 0) {
            if (matrix[i][j] > target)
                j--;
            else if (matrix[i][j] < target)
                i++;
            else
                return true;
        }
        return false;
    }
};

TEST_CASE("Benchmark Scale: 100 x 100", "[Small Scale Matrix]") {
    int m = 100;
    int n = 100;
    vector<vector<int>> matrix(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            matrix[i][j] = std::max(i >= 1 ? matrix[i - 1][j] : 0,
                                    j >= 1 ? matrix[i][j - 1] : 0) +
                           rand() % 10 + 1;
        }

    Solution1 s1;
    Solution2 s2;

    BENCHMARK("Benchmark Solution1 O(log(m*n))") {
        // Generates random integer in [0, max]
        int target =
            (int)(((float)rand() / (float)RAND_MAX) * matrix[m - 1][n - 1]);
        s1.searchMatrix(matrix, target);
    };
    BENCHMARK("Benchmark Solution2 O(m+n)") {
        int target =
            (int)(((float)rand() / (float)RAND_MAX) * matrix[m - 1][n - 1]);
        s2.searchMatrix(matrix, target);
    };
}

TEST_CASE("Benchmark Scale: 100 x 10000", "[Un-Balanced Scale Matrix]") {
    int m = 100;
    int n = 10000;
    vector<vector<int>> matrix(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            matrix[i][j] = std::max(i >= 1 ? matrix[i - 1][j] : 0,
                                    j >= 1 ? matrix[i][j - 1] : 0) +
                           rand() % 10 + 1;
        }

    Solution1 s1;
    Solution2 s2;

    BENCHMARK("Benchmark Solution1 O(log(m*n))") {
        // Generates random integer in [0, max]
        int target =
            (int)(((float)rand() / (float)RAND_MAX) * matrix[m - 1][n - 1]);
        s1.searchMatrix(matrix, target);
    };
    BENCHMARK("Benchmark Solution2 O(m+n)") {
        int target =
            (int)(((float)rand() / (float)RAND_MAX) * matrix[m - 1][n - 1]);
        s2.searchMatrix(matrix, target);
    };
}

TEST_CASE("Benchmark Scale: 10000 x 10000", "[Large Scale Matrix]") {
    int m = 10000;
    int n = 10000;
    vector<vector<int>> matrix(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            matrix[i][j] = std::max(i >= 1 ? matrix[i - 1][j] : 0,
                                    j >= 1 ? matrix[i][j - 1] : 0) +
                           rand() % 10 + 1;
        }

    Solution1 s1;
    Solution2 s2;

    BENCHMARK("Benchmark Solution1 O(log(m*n))") {
        // Generates random integer in [0, max]
        int target =
            (int)(((float)rand() / (float)RAND_MAX) * matrix[m - 1][n - 1]);
        s1.searchMatrix(matrix, target);
    };
    BENCHMARK("Benchmark Solution2 O(m+n)") {
        int target =
            (int)(((float)rand() / (float)RAND_MAX) * matrix[m - 1][n - 1]);
        s2.searchMatrix(matrix, target);
    };
}
