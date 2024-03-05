#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int N = 1e5 + 1;

using P = pair<int, int>;  // (距离 or 边权, 节点号)
vector<vector<P>> edges;   // edges[x] => {{w, y}}  边权,邻接点
int n;
int s = 1;  // 出发点
int f[N];   //  s 到 x 的最短路

// 小根堆
priority_queue<P, vector<P>, greater<P>> q;
bool vis[N];  // 访问数组

void dijkstra() {
    memset(f, 0x3f, sizeof f);
    memset(vis, 0, sizeof vis);
    f[s] = 0;
    q.push({f[s], s});
    while (!q.empty()) {
        auto [_, x] = q.top();
        q.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (const auto& p : edges[x]) {
            auto [w, y] = p;
            if (f[y] > f[x] + w) {
                f[y] = f[x] + w;
                q.push({f[y], y});
            }
        }
    }
}
