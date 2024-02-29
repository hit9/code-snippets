#include <functional>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
   public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses,
                  int k) {
        // 预处理边
        int n = edges.size() + 1;
        vector<vector<int>> ed(n);
        for (auto& e : edges) {
            ed[e[0]].push_back(e[1]);
            ed[e[1]].push_back(e[0]);
        }
        // 预处理猜测 g[father] -> child
        vector<unordered_set<int>> g(n);
        for (auto& gs : guesses) {
            g[gs[0]].insert(gs[1]);
        }

        vector<int> f(n, 0);  // f[x] 表示以 x 为根的子树的正确答案数
        vector<bool> vis(n, false);

        function<void(int)> up = [&](int x) {
            vis[x] = true;
            for (auto y : ed[x]) {
                if (vis[y]) continue;
                up(y);
                f[x] += f[y];
                // (x, y) 是否是命中
                if (g[x].find(y) != g[x].end()) ++f[x];
            }
        };
        up(0);

        fill(vis.begin(), vis.end(), false);
        function<void(int)> down = [&](int x) {
            vis[x] = true;
            for (auto y : ed[x]) {
                if (vis[y]) continue;
                int z = f[x] - f[y];  // 撤销 y 原本对 x 的贡献
                // (x, y) 是否是命中, 撤销贡献
                if (g[x].find(y) != g[x].end()) --z;
                f[y] += z;
                // (y, x) 是否命中, 加入贡献
                if (g[y].find(x) != g[y].end()) ++f[y];
                down(y);
            }
        };
        down(0);

        int ans = 0;
        for (int x = 0; x < n; x++)
            if (f[x] >= k) ans++;
        return ans;
    }
};
