#include <cstring>
#include <vector>

using namespace std;

const int inf = 0x3f3f3f3f;

class BIT {
   private:
    int n;
    vector<int> c;
    vector<int> a;

   public:
    explicit BIT(int n)
        : n(n), c(vector<int>(n + 1, inf)), a(vector<int>(n + 1, inf)) {}

    int lowbit(int x) { return x & -x; }

    int ask(int l, int r) {
        int ans = inf;

        while (r >= l) {
            for (; r - lowbit(r) + 1 > l; r -= lowbit(r)) ans = min(c[r], ans);
            ans = min(a[r--], ans);
        }
        return ans;
    }
    void update(int x, int v) {
        a[x] = v;
        for (; x <= n; x += lowbit(x)) c[x] = min(c[x], v);
    }
};

class Solution {
   public:
    int minimumVisitedCells(vector<vector<int>>& g) {
        int m = g.size(), n = g[0].size();

        // f[i][j] 表达为 [i,j] 到达终点的最少步数
        // 但是转移会超时, 所以用树状数组维护

        // 按列连续映射
        auto q1 = [&](int i, int j) { return i * n + j + 1; };

        // 按行连续映射
        auto q2 = [&](int i, int j) { return j * m + i + 1; };

        // 树状数组维护 f 的最小值, 区间下标 [1..m*n]
        BIT b1(m * n), b2(m * n);
        b1.update(q1(m - 1, n - 1), 1);
        b2.update(q2(m - 1, n - 1), 1);

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i == m - 1 && j == n - 1) continue;

                int v = inf;

                // 向右走
                if (j != n - 1 && g[i][j] > 0)  // [i,j+1] ~ [i, j+g[i][j]]
                    v = min(v, b1.ask(q1(i, j + 1),
                                      q1(i, min(j + g[i][j], n - 1))));

                // 向下走
                if (i != m - 1 && g[i][j] > 0)  // [i+1,j] ~ [i+g[i][j], j]
                    v = min(v, b2.ask(q2(i + 1, j),
                                      q2(min(i + g[i][j], m - 1), j)));

                if (v != inf) {
                    b1.update(q1(i, j), v + 1);
                    b2.update(q2(i, j), v + 1);
                }
            }
        }

        int ans = b1.ask(1, 1);
        if (ans >= inf) return -1;
        return ans;
    }
};
