// https://www.luogu.com.cn/problem/P1775

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int solve(const vector<int> &a, int n) {
    // 先计算前缀和
    // sum[i] 表示 [1,i] 的前缀和
    vector<int> sum(n + 1, 0);
    sum[1] = a[1];
    for (int i = 2; i <= n; i++) sum[i] = sum[i - 1] + a[i];

    // dp[i][j] 表示完成区间 [i, j] 的合并所需要的最小代价
    int dp[n + 1][n + 1];
    memset(dp, 0x3f, sizeof dp);

    // [i,i] 单元素区间合并成本是 0
    for (int i = 1; i <= n; i++) dp[i][i] = 0;

    // 递推关系: min(dp[i][k] + dp[k+1][j] for k between (i, j)) + sum[i,j]
    // 要从小的长度到大的长度迭代
    // x 是区间长度, 至少是 2; 区间左端是 i, 右端就是 i + x - 1
    for (int x = 2; x <= n; x++) {
        for (int i = 1; i <= n - x + 1; i++) {  // j <= n  即 i + x - 1 <= n
            int j = i + x - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
            dp[i][j] += sum[j] - sum[i - 1];
        }
    }
    return dp[1][n];
}

int main(void) {
    int n;
    cin >> n;
    getchar();
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    cout << solve(a, n) << endl;
    return 0;
}
