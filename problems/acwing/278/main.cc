#include <cstdio>
#include <cstring>

using namespace std;

const int N = 110;
const int M = 10010;

int n, m;

int a[N];
int f[M];

int solve() {
    memset(f, 0, sizeof f);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= a[i]; j--) f[j] += f[j - a[i]];
    return f[m];
}

int main(void) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    printf("%d\n", solve());
    return 0;
}
