#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 2001;

int n;
int a[N];
int f[5];  // state1    1..1
           // state2    1..12..2
           // state3    1..12..21..1
           // state4    1..12..21..12..2

int solve() {
    memset(f, 0, sizeof f);

    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            f[1]++;
            f[3] = max(f[2], f[3]) + 1;
        } else {  // 2
            f[2] = max(f[1], f[2]) + 1;
            f[4] = max(f[3], f[4]) + 1;
        }
    }
    int ans = 0;
    for (int j = 1; j <= 4; j++) ans = max(ans, f[j]);
    return ans;
}

int main(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    printf("%d\n", solve());
    return 0;
}
