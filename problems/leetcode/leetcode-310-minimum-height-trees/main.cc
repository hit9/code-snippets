#include <algorithm>
#include <functional>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>
using namespace std;

// 双 dp 换根

class Solution {
   public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // 预处理边, 因为是无向，所以建两个
        vector<vector<int>> ed(n);
        for (auto& e : edges) {
            ed[e[0]].push_back(e[1]);
            ed[e[1]].push_back(e[0]);
        }

        // f(x) 表示以 0 为根的时候的子树 x 的高
        // g(x) 表示以 0 为根的时候的子树 x 的次高
        // 如果有两个最高，次高就是最高
        vector<int> f(n, 0), g(n, 0);

        vector<bool> vis(n, false);

        // 假定一个根 0 ，计算每个子树的高度
        function<void(int)> up = [&](int x) {
            vis[x] = true;
            for (auto y : ed[x]) {
                if (vis[y]) continue;
                up(y);  // 先处理子树 y
                if (f[x] <= f[y] + 1) {
                    // 非第一次取最高，则提前记录次高
                    if (f[x] != 0) g[x] = f[x];
                    f[x] = f[y] + 1;
                }
            }
        };

        up(0);

        // 这一次
        // f[x] 表示以 x 为根的时候的树高
        // g[x] 表示以 x 为根的时候的次高
        // 仍从刚才的根 0 出发，前序修正 f, 注意情况访问数组
        fill(vis.begin(), vis.end(), false);

        function<void(int)> down = [&](int x) {
            vis[x] = true;

            // 预先计算，以 0 为根的情况下，
            // x 的下游最高子树有几个？
            int df = 0;
            for (auto y : ed[x]) {
                if (vis[y]) continue;  // 保证只访问下游
                if (f[y] + 1 == f[x]) df++;
            }

            // 换根
            for (auto y : ed[x]) {
                if (vis[y]) continue;
                // 注意需要同步维护 g[y] 的含义
                if (f[y] + 1 < f[x]) {
                    // y 不是 x 最高的子树, x 再算上 (x,y) 边肯定会更高
                    // y 的新次高要么是原来的 f[y], 要么是 g[x]+1
                    // TODO: g[x] 会不会是唯一的 y？
                    g[y] = max(f[y], g[x] + 1);
                    f[y] = f[x] + 1;
                } else if (f[y] + 1 == f[x]) {
                    // y 是 x 的一颗最高的子树
                    // 进一步考虑 x 的次高
                    if (f[y] < g[x] + 1) {
                        // x 存在一个次高子树 z，可以联合 (x,y) 成为 y 的最高
                        // 由于 y 是 x 最高的子树，所以此时 z 一定和 y 同高
                        // 那么 y 和 z 至少有一个在以 0 为根的情况下处于 x
                        // 的下游.
                        // 如果 df == 1, 也就是除了 y 和 z，x 没有更高的子树了
                        // 那么 y 新的次高只能是原本的 f[y]
                        if (df == 1) g[y] = f[y];
                        // 否则 df > 1, 还存在其他最高子树，那么 y
                        // 新的次高肯定也是新的最高
                        else
                            g[y] = g[x] + 1;
                        f[y] = g[x] + 1;
                    } else {
                        // 否则 y 是 x 唯一的最高子树, f[y] 不变
                        // g[y] 需要和 g[x]+1 取最值
                        g[y] = max(g[y], g[x] + 1);
                    }
                }
                down(y);
            }
        };

        down(0);

        // 答案收集
        vector<int> ans;
        auto min_h = *min_element(f.begin(), f.end());
        for (int x = 0; x < n; x++)
            if (min_h == f[x]) ans.push_back(x);
        return ans;
    }
};
