#include <cstring>
#include <utility>
#include <vector>

using namespace std;

int n;  // 节点数
const int N = 1e5 + 1;

using P = pair<int, int>;

// edges[x] = {(y, w)} 表示 x 和 y 之间有一条有向边, 权值是 w
vector<vector<P>> edges;

// f[i][j] 表示 i 到 j 的最短路结果
int f[N][N];

void floyd() {
    memset(f, 0x3f, sizeof f);

    // 初始化相邻边的最短路
    for (int i = 1; i <= n; i++)
        for (const auto& p : edges[i]) f[i][p.first] = p.second;

    // 按 k 划分阶段
    // 表示只考虑 i 和 j 之间经过 [1..k] 内的点的情况
    // 阶段进行时, 考虑放入第 k 个路过点, 即新增把 k
    // 当做分割点的情况,综合取最小值
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
}
