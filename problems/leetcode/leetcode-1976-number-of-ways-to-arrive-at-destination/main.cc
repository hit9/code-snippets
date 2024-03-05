#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;
using P = pair<ll, int>;  // w,y
const ll MOD = 1e9 + 7;
const int N = 205;

class Solution {
   public:
    vector<vector<P>> edges;
    ll f[N];  // 最短路
    ll g[N];  // 计数
    bool vis[N];
    priority_queue<P, vector<P>, greater<P>> q;

    void dijkstra(int s, int n) {
        memset(f, 0x3f, sizeof f);
        for (int i = 0; i <= n; i++) g[i] = 1;  // 至少为1
        memset(vis, 0, sizeof vis);

        f[s] = 0, g[s] = 1;
        q.emplace(f[s], s);

        while (q.size()) {
            auto x = q.top().second;
            q.pop();
            if (vis[x]) continue;
            vis[x] = true;
            for (const auto& p : edges[x]) {
                ll w = p.first;
                int y = p.second;
                // 经过 x 到达 y
                if (f[y] > f[x] + w) {
                    // 最短路得到更新, 重置为 g[x]
                    f[y] = f[x] + w;
                    g[y] = g[x] % MOD;
                    q.emplace(f[y], y);
                } else if (f[y] == f[x] + w) {
                    // 经过 x 到达 y 命中最短路, 加上数目
                    g[y] += g[x] % MOD;
                }
            }
        }
    }

    int countPaths(int n, vector<vector<int>>& roads) {
        // 存边
        edges.resize(n);
        for (const auto& rd : roads) {
            auto u = rd[0], v = rd[1], t = rd[2];
            // 双向边
            edges[u].emplace_back(t, v);
            edges[v].emplace_back(t, u);
        }
        // 跑最短路
        dijkstra(0, n);
        int ans = g[n - 1] % MOD;
        return max(ans, 1);
    }
};
