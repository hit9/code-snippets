#include <cstdio>
#include <vector>

using namespace std;

const int N = 302;
const int M = 301;

int n, m;  // 物品数量, 背包体积

// f[x][j] 表示只考虑子树 x 的子问题时选取总体积 j 的最大价值
int f[N][M];

// 父节点到子节点的边 edges[father] = {children..}
// 注意 0 号是虚拟节点
vector<int> edges[N];

// 价值数组, 即学分
int w[N];

// dfs 处理子树 x 的答案
// 以节点(物品)划分阶段, 不断加入物品 x
// 考虑 x 的时候, 因为 y 依赖 x, 所以可以进一步考虑子节点 y, 也可以不选
// 因此要先递归处理子孙, 分成两部分计算:
// 1. 子孙的贡献
// 2. x 自身的贡献
void dfs(int x) {
    f[x][0] = 0;                                  // 初始化
    for (int j = 1; j <= m; j++) f[x][j] = w[x];  // 至少选择 x
    // 考虑选择一个子树 y, 子孙的贡献
    for (auto y : edges[x]) {
        dfs(y);
        // 依次考虑每个体积, 每个物品只考虑一次, 所以倒序
        // 因为 f[x][j-k] 会对 f[x][j] 形成转移, 所以迭代方向要和 j
        // 的迭代方向逆过来;
        // j 至少为 v[x], 保证选择 x
        for (int j = m; j >= 1; j--) {
            // 枚举子树 y 的分配 (即子树 y 内选 k 门颗), 至多为 j-v[x]
            for (int k = 0; k <= j - 1; k++) {
                // x 的其他子树和x本身,总共选 j-k 门课
                f[x][j] = max(f[x][j], f[y][k] + f[x][j - k]);
            }
        }
    }
}

int solve() {
    dfs(0);
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
