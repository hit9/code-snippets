// 只求长度的版本
// https://www.acwing.com/problem/content/description/274/

#include <algorithm>
#include <iostream>

using namespace std;

const int N = 3010;

int a[N];  // 第 1 个数组
int b[N];  // 第 2 个数组
int c[N];  // 结果

int n;

// dp[i][j] 表示 a[1..i] 和 b[1..j] 上的以 b[j] 结尾的 LCIS 长度
int dp[N][N] = {0};

int solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // mx 跟进 dp[i-1][k] (k 属于 0..j) 上的满足 b[k] < a[i]=b[j] 的 dp
        // 最大值
        int mx = 0;
        for (int j = 1; j <= n; j++) {
            if (a[i] != b[j])
                dp[i][j] = dp[i - 1][j];
            else {  // a[i] == b[j]
                dp[i][j] = mx + 1;
            }
            if (b[j] < a[i]) mx = std::max(mx, dp[i - 1][j]);
            ans = std::max(dp[i][j], ans);
        }
    }
    return ans;
}

int main(void) {
    // 输入第 1 个序列
    cin >> n;
    getchar();
    for (int i = 1; i <= n; i++) cin >> a[i];
    getchar();

    // 输入第 2 个序列
    for (int i = 1; i <= n; i++) cin >> b[i];
    getchar();

    // 输出结果
    int q = solve();
    cout << q << endl;

    return 0;
}
