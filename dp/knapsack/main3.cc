#include <algorithm>
#include <cstring>
using namespace std;

// 多重背包

const int N = 10005;
const int M = 10005;

int v[N], w[N], c[N];  // 物品体积、价值、每种物品的个数
int n, m;              // 物品种数、背包体积

int f[M];  // 背包放入总体积为 j 的物品的最大价值 f[j]

int solve() {
    memset(f, 0xcf, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= n; i++) {           // 物品种数
        for (int k = 1; k <= c[i]; k++)      // 每种物品的个数
            for (int j = m; j >= v[i]; j--)  // 体积
                f[j] = max(f[j], f[j - v[i]] + w[i]);
    }
    int ans = 0;
    for (int j = 0; j <= m; j++) ans = max(ans, f[j]);
    return ans;
}
