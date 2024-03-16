// P2014 拓扑排序逆序 dp 的思路

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int N = 302;
const int M = 301;

int n, m;  // 物品数量, 背包体积

// 父节点到子节点的边 edges[father] = {children..}
vector<int> edges[N];

// 价值数组, 即学分
int w[N];

// 节点的拓扑序
int seq[N];

// 节点入度
int deg[N];

// 拓扑序倒序加入物品
// f[x][j] 表示放入物品 x 时选取总体积 j 的最大价值
int f[N][M];

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
    // 以物品划分阶段, 先考虑依赖的最底层
    // 倒序考虑加入每个物品 x
    // 选择 x 的前提下, 可以进一步选择依赖它的 y, 也可以不选择
    // 所以 x 要并入 y 的贡献, 所以要倒序
    for (int i = n; i >= 0; i--) {
        int x = seq[i];
        // 初始化
        f[x][0] = 0;
        for (int j = 1; j <= m; j++) f[x][j] = w[x];  // 至少选择 x
        // 考虑继续选择一个 y 的新增贡献
        for (auto y : edges[x]) {
            // 考虑每个背包体积, 至少为 j-v[x]
            for (int j = m; j >= 1; j--) {
                // 枚举分配给 y 的体积 k, 分配给其余的y和x 的即是 j-k
                for (int k = 0; k <= j - 1; k++) {
                    f[x][j] = max(f[x][j], f[y][k] + f[x][j - k]);
                }
            }
        }
    }

    return f[0][m];
}

int main(void) {
    scanf("%d%d", &n, &m);
    // 虚拟0号节点,学分是 0
    w[0] = 0;
    // 0 号是必选所以
    m++;
    int k = n, y = 1;
    while (k--) {
        int x;  // x 是 y 的先修
        scanf("%d%d", &x, &w[y]);
        // x = 0 时表示没有先修, 也就是 0 号作为先修
        edges[x].push_back(y);
        y++;
    }

    printf("%d\n", solve());
    return 0;
}
