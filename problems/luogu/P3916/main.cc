#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
vector<vector<int>> edges;
int n;        // 节点数目
int A[N];     // 答案
bool vis[N];  // 访问数组

void dfs(int x) {
    vis[x] = true;
    for (auto y : edges[x]) {
        if (vis[y]) continue;
        A[y] = max(A[y], A[x]);
        dfs(y);
    }
}

void solve() {
    memset(vis, 0, sizeof vis);
    memset(A, 0, sizeof A);
    // 至少可以到达自身
    for (int x = 1; x <= n; x++) A[x] = x;
    // 反向 DFS O(n^2)
    for (int x = n; x >= 1; x--)
        if (!vis[x]) dfs(x);
}

int main(void) {
    int m;
    scanf("%d%d", &n, &m);
    // 反向建图 (边反过来)
    edges.resize(n + 1);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[y].push_back(x);
    }
    solve();
    for (int x = 1; x <= n; x++) printf("%d ", A[x]);
    putchar('\n');
    return 0;
}
