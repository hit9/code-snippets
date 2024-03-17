#include <cstdio>
#include <cstring>
#include <vector>

// P1272
// 一个以1号节点为根的有向树,最少断几个边可以分离出一颗节点数目恰好为 P
// 的子树出来.

using namespace std;

const int N = 151;

int n, p;

// 边
vector<int> edges[N];

// f[x][j] 表示子树 x 分离出来大小为 j 的子树, 且包含 x 的
// 最少需要删除的边的数目
int f[N][N];

// dfs 处理 f
void dfs(int x) {
    f[x][1] = edges[x].size();  // 只保留 x 的时候
    for (auto y : edges[x]) {
        dfs(y);
        // 枚举要保留的节点大小 j, 必须保留 x, 所以 j 至少1
        for (int j = p; j >= 1; j--) {
            // 枚举子树 y 中分配了多少节点 k, 至多 j - 1 (保留 x)
            for (int k = 1; k <= j - 1; k++) {
                // 因为必须保留子树 y, 所以边 (x,y) 不能删
                // 那么就应该采用 f[x][j-k] - 1
                f[x][j] = min(f[x][j], f[y][k] + f[x][j - k] - 1);
            }
        }
    }
}

int solve() {
    memset(f, 0x3f, sizeof f);
    dfs(1);

    // 答案取整体最小
    // 注意,根节点的时候,即 f[1][p]
    int ans = f[1][p];
    // 但是其他节点,要考虑把它和上游的连接也切掉,所以+1
    for (int x = 2; x <= n; x++) ans = min(ans, f[x][p] + 1);
    return ans;
}

int main(void) {
    scanf("%d%d", &n, &p);
    int k = n - 1;
    while (k--) {
        int fa, x;
        scanf("%d%d", &fa, &x);
        edges[fa].push_back(x);
    }
    printf("%d\n", solve());
    return 0;
}
