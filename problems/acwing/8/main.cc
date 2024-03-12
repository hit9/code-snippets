#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1000 + 1;
const int MAX_M = 101;
const int MAX_V = 101;
int v[N];             // 物品体积
int m[N];             // 物品重量
int w[N];             // 物品价值
int f[MAX_M][MAX_V];  // dp 价值
int n, V, M;          // 物品件数, 体积限制, 重量限制

int solve() {
    memset(f, 0xcf, sizeof f);
    f[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = V; j >= v[i]; j--) {
            for (int k = M; k >= m[i]; k--) {
                f[j][k] = max(f[j][k], f[j - v[i]][k - m[i]] + w[i]);
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= V; j++)
    for (int k = 0; k <= M; k++) ans = max(ans, f[j][k]);
    return ans;
}

int main(void) {
    scanf("%d%d%d", &n, &V, &M);
    int k = n, i = 1;
    while (k--) {
        scanf("%d%d%d", &v[i], &m[i], &w[i]);
        i++;
    }
    printf("%d\n", solve());
    return 0;
}
