#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int M = 100000 + 5;

int m = 0;

int v[M];  // i 的体积, 就是 i^4
int f[M];  // 拼成 j 的最少的四次方数的个数

int solve() {
    if (m <= 0) return 0;

    // 预处理 v[i], k 表示总的物品数目, 注意从 1 开始
    int k = 1;
    while (1) {
        int s = k * k * k * k;
        if (s > m) break;
        v[k++] = s;
    }

    // 完全背包
    memset(f, 0x3f, sizeof f);
    f[0] = 0;

    for (int i = 1; i <= k; i++) {
        for (int j = v[i]; j <= m; j++) {
            f[j] = min(f[j], f[j - v[i]] + 1);
        }
    }

    return f[m];
}

int main(void) {
    scanf("%d", &m);
    printf("%d\n", solve());
    return 0;
}
