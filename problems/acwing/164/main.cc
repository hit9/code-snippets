#include <bitset>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int N = 30000 + 5;
int n;
vector<vector<int>> edges;
int ans[N];
int a[N];  // topo order
int deg[N];

void toposort() {
    memset(deg, 0, sizeof deg);
    for (int x = 1; x <= n; x++)
        for (auto y : edges[x]) ++deg[y];

    queue<int> q;
    for (int x = 1; x <= n; x++)
        if (deg[x] == 0) q.push(x);

    int cnt = 0;
    while (!q.empty()) {
        auto x = q.front();
        q.pop();
        a[++cnt] = x;
        for (auto y : edges[x]) {
            if (--deg[y] == 0) q.push(y);
        }
    }
}

void solve() {
    toposort();

    // 第 x 位比特表示是否可以到达
    vector<bitset<N>> V(n + 1, 0);

    // 从后向前
    for (int j = n; j >= 1; j--) {
        auto x = a[j];
        // 可以到达自身
        V[x].set(x);
        // 可以到达 y 到达的点
        for (auto y : edges[x]) V[x] |= V[y];
    }

    // 答案
    memset(ans, 0, sizeof ans);
    for (int x = 1; x <= n; x++) {
        // 计算 1 的位数
        ans[x] = V[x].count();
    }
}

int main(void) {
    int m;
    scanf("%d%d", &n, &m);
    edges.resize(n + 1);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].push_back(y);
    }
    solve();
    for (int x = 1; x <= n; x++) printf("%d\n", ans[x]);
    return 0;
}
