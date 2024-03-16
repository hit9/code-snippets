#include <algorithm>
#include <cstdio>
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

void dfs(int x) {
    f[x][0] = 0;  // 注意初始化

    // 下面两种情况是可以选择 x 的情况:
    // 考虑子孙的贡献 (增量)
    for (auto y : edges[x]) {
        // 因为 y 依赖 x, 所以选择 x, 就可以进一步选择 y, 当然也可以不选
        // 所以, 要先处理完 y
        dfs(y);

        for (int j = m; j >= 0; j--) {  // 枚举 x 的分配体积 j, 至少为 v[x]
            for (int k = 0; k <= j; k++) {  // 枚举子树 y 的分配体积 k
                f[x][j] = max(f[x][j], f[y][k] + f[x][j - k]);
            }
        }
    }
    // 考虑 x 自身带来的贡献
    for (int j = m; j >= v[x]; j--) f[x][j] = f[x][j - v[x]] + w[x];

    // 如果背包体积过小, 注意设置 f[x][j] 为 0, 此时无法选择 x, 所以抹 0
    for (int j = 0; j < v[x]; j++) f[x][j] = 0;
}

int solve() {
    dfs(root);
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
