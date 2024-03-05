#include <cstdio>
#include <cstring>  // for memset
#include <queue>
#include <vector>

using namespace std;

const int N = 1e5 + 1;

int n;  // 节点数量
// a 的个数游标,从1开始
int tot = 0;
// 存图 edges[x] => {y1, y2, y3..}
vector<vector<int>> edges;
// 入度表
int deg[N];
// 拓扑排序结果
int a[N];

void toposort() {
    // 初始化入度表
    memset(deg, 0, sizeof deg);
    for (int x = 1; x <= n; x++)
        for (auto y : edges[x]) ++deg[y];

    queue<int> q;
    for (int x = 1; x <= n; x++)
        if (deg[x] == 0) q.push(x);

    while (!q.empty()) {
        auto x = q.front();
        q.pop();
        a[++tot] = x;
        for (auto y : edges[x]) {
            if (--deg[y] == 0) q.push(y);
        }
    }
}

int main(void) {
    int m;  // 边的数目
    scanf("%d%d", &n, &m);
    edges.resize(n + 1);

    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].push_back(y);
    }

    toposort();

    for (int x = 1; x <= n; x++) printf("%d\n", a[x]);
    return 0;
}
