// https://leetcode.cn/problems/number-of-islands/description/
// 200. 岛屿数量
// 并查集做法
// i*n+j 作为标号

#include <iostream>
#include <vector>

using namespace std;
class UnionFind {
   private:
    vector<int> pa;
    vector<int> sizes;
    int k;  // 孤岛数量

   public:
    explicit UnionFind(int n)
        : pa(vector<int>(n, 0)), sizes(vector<int>(n, 1)), k(n) {
        for (int i = 0; i < n; i++) pa[i] = i;
    }

    int Find(int x) {
        if (x == pa[x]) return x;
        return pa[x] = Find(pa[x]);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        if (sizes[x] < sizes[y]) {
            pa[x] = y;
            sizes[y] += sizes[x];
        } else {
            pa[y] = x;
            sizes[x] += sizes[y];
        }
        k--;
    }

    int K() { return k; }
};
class Solution {
   public:
    int numIslands(vector<vector<char>>& g) {
        int m = g.size();
        int n = g[0].size();

        UnionFind uf(m * n);

        auto f = [=](int i, int j) { return i * n + j; };

        // 注意刨除 0 的数量
        int k0 = 0;

        for (auto i = 0; i < m; i++) {
            for (auto j = 0; j < n; j++) {
                if (g[i][j] == '1') {
                    // 上
                    if (i > 0 && g[i - 1][j] == '1')
                        uf.Union(f(i, j), f(i - 1, j));
                    // 左
                    if (j > 0 && g[i][j - 1] == '1')
                        uf.Union(f(i, j), f(i, j - 1));
                } else
                    k0++;
            }
        }

        return uf.K() - k0;
    }
};

int main(void) {
    Solution solution;
    vector<vector<char>> g{{'1', '1', '1', '1', '1', '0', '1', '1', '1', '1'},
                           {'1', '0', '1', '0', '1', '1', '1', '1', '1', '1'},
                           {'0', '1', '1', '1', '0', '1', '1', '1', '1', '1'},
                           {'1', '1', '0', '1', '1', '0', '0', '0', '0', '1'},
                           {'1', '0', '1', '0', '1', '0', '0', '1', '0', '1'},
                           {'1', '0', '0', '1', '1', '1', '0', '1', '0', '0'},
                           {'0', '0', '1', '0', '0', '1', '1', '1', '1', '0'},
                           {'1', '0', '1', '1', '1', '0', '0', '1', '1', '1'},
                           {'1', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
                           {'1', '0', '1', '1', '1', '1', '1', '1', '1', '0'}};
    cout << solution.numIslands(g) << endl;
}
