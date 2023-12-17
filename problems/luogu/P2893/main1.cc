#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

const int N = 2001;

// A 是原数组
int A[N];

// a 是离散化后的数组
int a[N];

// dp 数组
int f[N][N];

int solve(int n) {
    // 离散化：
    for (int i = 1; i <= n; i++) a[i] = A[i];
    sort(a + 1, a + n + 1);
    int m = unique(a + 1, a + n + 1) - (a + 1);

    // DP 求解
    memset(f, 0x3f, sizeof f);     // inf
    memset(f[0], 0, sizeof f[0]);  // i=0
    for (int i = 1; i <= n; i++) {
        int mi = 0x3f3f3f3f;
        for (int j = 1; j <= m; j++) {
            // mi 同步跟进上一行 f[i-1] 中 <=j 的最小值
            mi = min(mi, f[i - 1][j]);
            f[i][j] = mi + abs(A[i] - a[j]);
        }
    }
    // 答案是 i=n 时可取到的最小值
    return *min_element(f[n], f[n] + n + 1);
}

int main(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];

    // 求非降情况
    int ans1 = solve(n);
    // 反向后求非增
    reverse(A + 1, A + n + 1);
    int ans2 = solve(n);
    cout << min(ans1, ans2) << endl;

    return 0;
}
