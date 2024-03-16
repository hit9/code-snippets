// 拓扑序版本

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int N = 101;
const int M = 101;

int n, m;  // 物品数量, 背包体积
int root;  // 根编号

// f[x][j] 表示只考虑子树 x 的子问题时选取总体积 j 的最大价值
int f[N][M];

// 父节点到子节点的边 edges[father] = {children..}
vector<int> edges[N];

// 体积, 价值数组
int v[N], w[N];

// 节点的拓扑序
int seq[N];

// 节点入度
int deg[N];

// 计算拓扑序到 seq 数组
void topo() {
    memset(deg, 0, sizeof deg);
    for (int x = 0; x <= n; x++)
        for (auto y : edges[x]) ++deg[y];
    queue<int> q;
    for (int x = 0; x <= n; x++)
        if (deg[x] == 0) q.push(x);
    int tot = 0;
    while (q.size()) {
        int x = q.front();
        q.pop();
        seq[tot++] = x;
        for (auto y : edges[x])
            if (--deg[y] == 0) q.push(y);
    }
}

int solve() {
    topo();
    for (int i = n; i >= 0; i--) {
        int x = seq[i];
        for (int j = v[x]; j <= m; j++) f[x][j] = w[x];  // 至少选择 x
        // 考虑继续选择一个 y 的新增贡献
        for (auto y : edges[x]) {
            // 考虑每个背包体积, 至少为 v[x]
            for (int j = m; j >= v[x]; j--) {
                // 枚举分配给 y 的体积 k, 分配给其余的y和x 的即是 j-k
                for (int k = 0; k <= j - v[x]; k++) {
                    f[x][j] = max(f[x][j], f[y][k] + f[x][j - k]);
                }
            }
        }
    }

    return f[root][m];
}

int main(void) {
    scanf("%d%d", &n, &m);

    int k = n, i = 1;
    while (k--) {
        int p;  // 父节点
        scanf("%d%d%d", &v[i], &w[i], &p);
        if (p == -1)
            root = i;  // 根编号
        else
            edges[p].push_back(i);
        i++;
    }

    printf("%d\n", solve());
    return 0;
}
