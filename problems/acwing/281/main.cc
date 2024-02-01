#include <cstdio>
#include <cstring>

#pragma GCC optimize(3)

using namespace std;

const int N = 101;
const int M = 1e5 + 10;
const int C = 1001;

int n, m;
int a[N], c[N];
bool f[M];
int used[M];

int solve() {
    memset(f, 0, sizeof f);
    f[0] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) used[j] = 0;
        for (int j = a[i]; j <= m; j++)
            if (!f[j] && f[j - a[i]] && used[j - a[i]] < c[i])
                f[j] = true, used[j] = used[j - a[i]] + 1;
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) ans += f[i];
    return ans;
}

int main(void) {
    while (1) {
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0) return 0;
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
        printf("%d\n", solve());
    }
    return 0;
}
