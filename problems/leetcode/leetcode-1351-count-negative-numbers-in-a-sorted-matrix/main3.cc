#include <iostream>
#include <vector>

using namespace std;

// 方法3: 四分取其三，O(log(mn))
// https://writings.sh/post/search-sorted-2d-matrix-revisited

// clang-format: off
//
//     -------------> 非递增
//
//  a 一定是最大
//
//    a ----- b ----- c
//    |       |       |
//    |   I   |  II   |
//    |       |       |   非递增
//    d ----- m ----- f     |
//    |       |       |     |
//    |  III  |   IV  |     V
//    |       |       |
//    g ----- h ----- z
//
//                      z 一定是最小
//
// clang-format: on

class Solution {
   public:
    // 统计当前矩阵中的负数, a 和 z 是当前矩阵的左上和右下的顶点
    int count(vector<vector<int>>& x, int ai, int aj, int zi, int zj) {
        // 递归终止: 越界
        if (ai > zi || aj > zj) return 0;

        auto a = x[ai][aj];  // 左上角
        auto z = x[zi][zj];  // 右下角

        // 顶点特判：

        // 递归终止: 只有一个元素的时候
        if (ai == zi && aj == zj) return a < 0 ? 1 : 0;

        // 最大的就是负数，则整个矩阵就是负数
        if (a < 0) return (zi - ai + 1) * (zj - aj + 1);
        // 最小的是非负数，则整个矩阵非负, 计数 0
        if (z >= 0) return 0;

        // 特判矩阵对角线 <= 2 个元素的情况，以防止取中点死递归
        // 现在已知 a >= 0 且 z < 0, 所以初始计数 1
        if (zi == ai + 1 && zj == aj) return 1;  // 两行一列, z 是负数
        if (zi == ai && zj == aj + 1) return 1;  // 一行两列, z 是负数
        if (zi == ai + 1 && zj == aj + 1) {
            // 两行两列, 分别检查 c 和 g 点是否是负数
            return 1 + (x[ai][zj] < 0 ? 1 : 0) + (x[zi][aj] < 0 ? 1 : 0);
        }

        // 取对角线中点
        // m 会最终算入 I 或者 IV 模块
        // 但是无论如何，m 这个点只会被考察一次
        auto mi = (ai + zi) / 2;
        auto mj = (aj + zj) / 2;
        auto m = x[mi][mj];

        int ans = 0;

        // 检查各个子模块，每次最差排除 1/4 部分
        // 也就是说，以 3/4 的速度减少面积
        // 必须检查 II (不含中点所在行和列)
        ans += count(x, ai, mj + 1, mi - 1, zj);

        // 必须检查 III (不含中点所在行和列)
        ans += count(x, mi + 1, aj, zi, mj - 1);

        if (m >= 0) {
            // 此时不必检查 I, 因为 I 都不小于 m, 肯定都非负
            // 只需要检查 IV (包括 m 所在的行和列)
            ans += count(x, mi, mj, zi, zj);
        } else {  // m < 0
            // 此时 IV 全部负数, 全部计入 (包括 m 所在的行和列)
            // 但是为了防止 m 被多算一次，所以要 -1
            ans += (zi - mi + 1) * (zj - mj + 1) - 1;
            // 然后只需要检查 I (包括 m 所在的行和列)
            ans += count(x, ai, aj, mi, mj);
        }
        return ans;
    }

    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        return count(grid, 0, 0, m - 1, n - 1);
    }
};

int main(void) {
    Solution s;
    vector<vector<int>> g{
        {4, 3, 2, -1}, {3, 2, 1, -1}, {1, 1, -1, -2}, {-1, -1, -2, -3}};
    cout << s.countNegatives(g) << endl;
    return 0;
}
