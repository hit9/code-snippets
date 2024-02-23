#include <cstdio>
#include <cstring>

using namespace std;

const int M = 1000;
int a[7];
int v[7] = {0, 1, 2, 3, 5, 10, 20};
int f[M + 1];

int solve() {
    memset(f, 0, sizeof f);

    f[0] = 1;
    for (int i = 1; i <= 6; i++)
        for (int k = 1; k <= a[i]; k++)
            for (int j = M; j >= v[i]; j--) f[j] += f[j - v[i]];

    int ans = 0;
    for (int j = 1; j <= M; j++) if(f[j]) ans ++;
    return ans;
}

int main(void) {
    for (int i = 1; i <= 6; i++) scanf("%d", &a[i]);
    printf("Total=%d\n", solve());
    return 0;
}
