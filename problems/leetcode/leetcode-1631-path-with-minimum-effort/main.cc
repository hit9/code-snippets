#include <cstdlib>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

using P = pair<int, int>;  // (w,y)

class Solution {
   public:
    int minimumEffortPath(vector<vector<int>>& h) {
        // 存边
        int m = h.size(), n = h[0].size();
        int N = m * n;
        vector<vector<int>> g(m, vector<int>(n, 0));
        int tot = -1;
        vector<vector<P>> edges(N);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = ++tot;
                if (i > 0) {
                    int w = abs(h[i][j] - h[i - 1][j]);
                    int y = g[i - 1][j];
                    edges[tot].push_back({w, y});
                    edges[y].push_back({w, tot});
                }
                if (j > 0) {
                    int w = abs(h[i][j] - h[i][j - 1]);
                    int y = g[i][j - 1];
                    edges[tot].push_back({w, y});
                    edges[y].push_back({w, tot});
                }
            }
        }

        // dijkstra
        vector<int> f(N, 0x3f3f3f3f);
        priority_queue<P, vector<P>, greater<P>> q;
        f[0] = 0;
        q.emplace(f[0], 0);
        vector<bool> vis(N, false);

        while (q.size()) {
            auto x = q.top().second;
            q.pop();
            if (vis[x]) continue;
            vis[x] = true;
            for (auto& p : edges[x]) {
                auto [w, y] = p;
                int v = max(f[x], w);
                if (f[y] > v) {
                    f[y] = v;
                    q.push({f[y], y});
                }
            }
        }

        return f[N - 1];
    }
};
