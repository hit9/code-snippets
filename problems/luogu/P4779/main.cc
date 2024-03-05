#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int N = 1e5 + 1;
int n;                     // 节点数
using P = pair<int, int>;  // (w,y)
vector<vector<P>> edges;   // edges[x] => (w,y) ...
int f[N];                  // 最短路
bool vis[N];               // 访问数组
int s;                     // 原点
priority_queue<P, vector<P>, greater<P>> q;

void dijkstra() {
    memset(f, 0x3f, sizeof f);
    memset(vis, 0, sizeof vis);
    f[s] = 0;
    q.emplace(0, s);
    while (!q.empty()) {
        auto x = q.top().second;
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
    scanf("%d%d%d", &n, &m, &s);
    edges.resize(n + 1);
    while (m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edges[u].emplace_back(w, v);
    }
    dijkstra();

    for (int x = 1; x <= n; x++) printf("%d ", f[x]);
    putchar('\n');
    return 0;
}
