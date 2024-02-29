#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>

using namespace std;

const int N = 2 * 1e5 + 5;

int f[N];
int n;                      // 节点数
vector<vector<int>> edges;  // 边 [x] => [y,z,...]
int ver[N];                 // 节点权值，1 表示白色，-1 表示黑色
bool vis[N];                // 访问数组

void solve() {
    memset(f, 0, sizeof f);
    memset(vis, 0, sizeof vis);

    function<void(int)> up = [&](int x) {
        vis[x] = true;
        f[x] = ver[x];  // 必选 x
        for (auto y : edges[x]) {
            if (vis[y]) continue;
            up(y);
            // 选or 不选子树 y
            if (f[y] > 0) f[x] += f[y];
        }
    };

    up(1);

    memset(vis, 0, sizeof vis);
    function<void(int)> down = [&](int x) {
        vis[x] = true;
        for (auto y : edges[x]) {
            if (vis[y]) continue;
            int fz = f[y] > 0 ? (f[x] - f[y]) : f[x];
            if (fz > 0) f[y] += fz;
            down(y);
        }
    };

    down(1);

    for (int x = 1; x <= n; x++) {
        printf("%d ", f[x]);
    }
    putchar('\n');
}

int main(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        ver[i] = (v == 1) ? 1 : -1;
    }
    int k = n - 1;
    edges.resize(n + 1);
    while (k--) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    solve();
    return 0;
}
