#include <bitset>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int N = 30000 + 1;
int n;
vector<vector<int>> edges;
int deg[N];                // 入度表
int seq[N];                // 拓扑序
bitset<N> from[N], to[N];  // 来源、可达的表

void topo() {
    memset(deg, 0, sizeof deg);
    memset(seq, 0, sizeof seq);
    // 入度表
    for (int x = 1; x <= n; x++)
        for (auto y : edges[x]) deg[y]++;
    // 拓扑排序
    queue<int> q;
    for (int x = 1; x <= n; x++)
        if (deg[x] == 0) q.push(x);
    int tot = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        seq[++tot] = x;
        for (auto y : edges[x])
            if (--deg[y] == 0) q.push(y);
    }
}

int solve() {
    topo();

    // 正序求来源, 不包含自身
    for (int j = 1; j <= n; j++) {
        int x = seq[j];
        for (auto y : edges[x]) {
            from[y][x] = 1;      // y 可来自 x
            from[y] |= from[x];  // y 可来自 x 的来源
        }
    }

    // 倒序求可达, 不包含自身
    for (int j = n; j >= 1; j--) {
        int x = seq[j];
        for (auto y : edges[x]) {
            to[x][y] = 1;    // x 可到达 y
            to[x] |= to[y];  // x 可到达 y 的到达
        }
    }

    int ans = 0;

    for (int x = 1; x <= n; x++) {
        for (auto y : edges[x]) {
            // 对于每一条边 (x,y)，如果存在一个点 z
            // x 可到达 z 且 z 可到达 y
            // 也就是 z 在 to[x] 中，也在 from[y] 中
            // 那么 (x,y) 就可以删掉
            ans += (to[x] & from[y]).any();
        }
    }
    return ans;
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
    printf("%d\n", solve());
    return 0;
}
