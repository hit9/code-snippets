#include <cstring>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

const int N = 101;
using P = pair<int, int>;  // {f, x}

class Graph {
   public:
    vector<P> ed[N];  // x => {w, y}

    Graph(int n, vector<vector<int>>& edges) {
        // 初始化存边
        for (auto& e : edges) ed[e[0]].emplace_back(e[2], e[1]);
    }

    void addEdge(vector<int> e) { ed[e[0]].emplace_back(e[2], e[1]); }

    // dijkstra
    int shortestPath(int s, int t) {
        // f[x] 表示从 s 到 x 的最短路
        int f[N];
        memset(f, 0x3f, sizeof f);
        f[s] = 0;

        // 访问数组
        bool vis[N];
        memset(vis, 0, sizeof vis);

        // 小根
        priority_queue<P, vector<P>, greater<P>> q;
        q.emplace(f[s], s);

        while (q.size()) {
            int x = q.top().second;
            q.pop();
            if (vis[x]) continue;
            vis[x] = true;
            for (auto& e : ed[x]) {
                int w = e.first, y = e.second;
                if (f[y] > f[x] + w) {
                    f[y] = f[x] + w;
                    q.emplace(f[y], y);
                }
            }
        }
        if (f[t] >= 0x3f3f3f3f) return -1;
        return f[t];
    }
};
