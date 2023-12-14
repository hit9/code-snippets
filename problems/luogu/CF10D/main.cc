// https://www.luogu.com.cn/problem/CF10D

#include <iostream>
#include <utility>

using namespace std;

const int N = 510;

int a[N];  // 第 1 个数组
int b[N];  // 第 2 个数组
int c[N];  // 用来回溯最长递增子序列

int n;  // a 的大小
int m;  // b 的大小

// dp[i][j] 表示 a[1..i] 和 b[1..j] 上的以 b[j] 结尾的 LCIS 长度
int dp[N][N] = {0};

// path[i][j] 表示 dp[i][j] 的位置
pair<int, int> path[N][N];

void solve() {
    // 最长 LCIS 长度, 取得答案的方格位置的 i, j 坐标
    int ans = 0, ans_i = 0, ans_j = 0;

    for (int i = 1; i <= n; i++) {
        // mx 跟进 dp[i-1][k] (k 属于 0..j) 上的满足 b[k] < a[i]=b[j] 的 dp
        // 最大值
        int mx = 0, mj = 0;

        for (int j = 1; j <= m; j++) {
            if (a[i] != b[j]) {
                dp[i][j] = dp[i - 1][j];
                path[i][j] = path[i - 1][j];
            } else {  // a[i] == b[j]
                dp[i][j] = mx + 1;
                // 记录由扩充来源
                path[i][j] = {i - 1, mj};
            }

            // 维护 mx 和 mj
            if (b[j] < a[i] && mx < dp[i - 1][j]) mx = dp[i - 1][j], mj = j;
            // 记录答案
            if (ans < dp[i][j]) ans = dp[i][j], ans_i = i, ans_j = j;
        }
    }

    // 输出长度
    cout << ans << endl;

    // 回溯一个最长序列
    int q = ans, i = ans_i, j = ans_j;

    while (q > 0) {
        // 只有 j > 0 才是真正的来源
        if (j > 0) c[q--] = b[j];
        auto &tmp = path[i][j];
        i = tmp.first, j = tmp.second;
    }
    // 反向打印
    for (int k = 1; k <= ans; k++) cout << c[k] << " ";
}

int main(void) {
    // 输入第 1 个序列
    cin >> n;
    getchar();
    for (int i = 1; i <= n; i++) cin >> a[i];
    getchar();

    // 输入第 2 个序列
    cin >> m;
    getchar();
    for (int i = 1; i <= m; i++) cin >> b[i];
    getchar();

    // 输出结果
    solve();
    return 0;
}
