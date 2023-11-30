// https://www.luogu.com.cn/problem/CF10D

#include <iostream>

using namespace std;

const int N = 510;

int a[N];  // 第 1 个数组
int b[N];  // 第 2 个数组
int c[N];  // 用来回溯最长递增子序列

int n;  // a 的大小
int m;  // b 的大小

// dp[i][j] 表示 a[1..i] 和 b[1..j] 上的以 b[j] 结尾的 LCIS 长度
int dp[N][N] = {0};

// path[i][j] = k 表示 dp[i][j] 的值来自于 (i-1, k)
int path[N][N];

void slove() {
    int ans = 0;               // 最长长度
    int ans_i = 0, ans_j = 0;  // 最长长度的来源位置

    for (int i = 1; i <= n; i++) {
        // mx 跟进 dp[i-1][k] (k 属于 0..j) 上的满足 b[k] < a[i]=b[j] 的 dp
        // 最大值
        int mx = 0;
        int mj = 0;

        for (int j = 1; j <= m; j++) {
            if (a[i] != b[j]) {
                dp[i][j] = dp[i - 1][j];
                // 拷贝来源
                path[i][j] = path[i - 1][j];
            } else {  // a[i] == b[j]
                dp[i][j] = mx + 1;
                // 真正来源
                path[i][j] = mj;
            }

            // 维护 mx 和 mj
            if (b[j] < a[i]) {
                if (mx < dp[i - 1][j]) {
                    mx = dp[i - 1][j];
                    mj = j;
                }
            }

            if (dp[i][j] > ans) {
                ans = dp[i][j];
                ans_i = i;
                ans_j = j;
            }
        }
    }

    // 输出长度
    cout << ans << endl;

    // 回溯一个最长序列
    int q = ans;
    int i = ans_i, j = ans_j;
    while (q > 0) {
        // 只有 j > 0 才是真正的来源
        if (j > 0) c[q--] = b[j];
        j = path[i][j];
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
    slove();
    return 0;
}
