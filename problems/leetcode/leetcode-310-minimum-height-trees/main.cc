#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // 预处理边, 因为是无向，所以建两个
        vector<vector<int>> ed(n);
        for (auto& e : edges) {
            ed[e[0]].push_back(e[1]);
            ed[e[1]].push_back(e[0]);
        }

        // h(x) 表示以 0 为根的时候的子树 x 的高
        // g(x) 表示以 0 为根的时候的子树 x 的次高, 允许并列
        vector<int> h(n, 0), g(n, 0);

        vector<bool> vis(n, false);

        function<void(int)> up = [&](int x) {
            vis[x] = true;
            for (auto y : ed[x]) {
                if (vis[y]) continue;
                up(y);  // 先处理子树 y
                if (h[x] < h[y] + 1) {
                    g[x] = h[x];
                    h[x] = h[y] + 1;
                } else if (g[x] < h[y] + 1) { // 这里注意别丢
                    g[x] = h[y] + 1;
                }
            }
        };

        up(0);

        // u[x] 表示以 x 为根时向外走的最大路径长度
        // 这里的外，是指不包括第一次以0为根扫描到的子树 x.
        vector<int> u(n, 0);
        // f[x] 是以 x 为根的树高，即答案
        vector<int> f(n, 0);
        // 从根 0 出发前序 dp，注意情况访问数组
        fill(vis.begin(), vis.end(), false);

        function<void(int)> down = [&](int x) {
            vis[x] = true;
            // 换根
            for (auto y : ed[x]) {
                if (vis[y]) continue;
                if (h[x] != g[x] && h[x] == h[y] + 1)
                    // y 是 x 的唯一最高子树
                    u[y] = max(u[x], g[x]) + 1;
                else
                    // 否则 y 之外必然有一个最高子树
                    u[y] = max(u[x], h[x]) + 1;
                f[y] = max(u[y], h[y]);
                down(y);
            }
        };
        f[0] = h[0];
        down(0);

        // 答案收集
        vector<int> ans;
        auto min_f = *min_element(f.begin(), f.end());
        for (int x = 0; x < n; x++)
            if (min_f == f[x]) ans.push_back(x);
        return ans;
    }
};
