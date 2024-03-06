#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

const int N = 1e3 + 1;
using P = pair<int, int>;  // (w, y)
int n;
vector<vector<P>> edges1, edges2;  // 正向图, 反向图
priority_queue<P, vector<P>, greater<P>> q1, q2;
int f1[N], f2[N];
bool vis1[N], vis2[N];

void dijkstra(int (&f)[N], int s, vector<vector<P>>& edges,
              priority_queue<P, vector<P>, greater<P>>& q, bool (&vis)[N]) {
    memset(f, 0x3f, sizeof f);
    memset(vis, 0, sizeof vis);
    f[s] = 0;
    q.emplace(f[s], s);
    while (q.size()) {
        int x = q.top().second;
        q.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (const auto& p : edges[x]) {
            auto [w, y] = p;
            if (f[y] > f[x] + w) {
                f[y] = f[x] + w;
                q.emplace(f[y], y);
            }
        }
    }
}

int main(void) {
    int m;
    scanf("%d%d", &n, &m);
    edges1.resize(n + 1);
    edges2.resize(n + 1);
    while (m--) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        edges1[x].push_back({w, y});
        edges2[y].push_back({w, x});
    }
    dijkstra(f1, 1, edges1, q1, vis1);
    dijkstra(f2, 1, edges2, q2, vis2);

    int ans = 0;
    for (int x = 1; x <= n; x++) ans += f1[x] + f2[x];  // 正向 + 反向

    printf("%d\n", ans);
    return 0;
}
