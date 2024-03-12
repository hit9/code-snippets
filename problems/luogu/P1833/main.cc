#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 10000 + 1;
const int MAX_M = 1001;
int f[MAX_M];
int p[N], v[N], w[N];  // 次数限制数组, 体积数组, 价值数组
int n, m;              // m 是总的分钟数

int solve() {
    memset(f, 0xcf, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {  // 完全背包
            for (int j = v[i]; j <= m; j++) {
                f[j] = max(f[j], f[j - v[i]] + w[i]);
            }
        } else if (p[i] == 1) {  // 01 背包
            for (int j = m; j >= v[i]; j--) {
                f[j] = max(f[j], f[j - v[i]] + w[i]);
            }
        } else {  // 多重背包
            for (int k = 1; k <= p[i]; k++) {
                for (int j = m; j >= v[i]; j--) {
                    f[j] = max(f[j], f[j - v[i]] + w[i]);
                }
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= m; j++) ans = max(ans, f[j]);
    return ans;
}

int main(void) {
    int hhs, mms, hhe, mme;
    scanf("%d:%d %d:%d %d", &hhs, &mms, &hhe, &mme, &n);
    m = 60 * (hhe - hhs) + (mme - mms);  // 分钟数
    int k = n, i = 1;
    while (k--) {
        scanf("%d%d%d", &v[i], &w[i], &p[i]);
        i++;
    }
    printf("%d\n", solve());
    return 0;
}
