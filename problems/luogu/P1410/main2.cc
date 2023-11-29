// https://www.luogu.com.cn/problem/P1410

#include <cstring>
#include <iostream>

const int inf = 0x3f3f3f3f;

int a[2010];
int dp[2010][2010];

using namespace std;

// dp[i][j] 的定义:
// 当前已经枚举了 i 个元素, 且 a[i-1] 元素落在序列 x 的尾部
// 假序列 x 的长度是 j, 那么另一个序列 y 的长度是 i-j
// dp[i][j] 记录序列 y 的末尾元素的最小值
//
// 考虑下一个元素 a[i]
// 如果放入序列 x，前提是 a[i-1] < a[i]，也就是要满足递增条件.
// 此时另一个序列 y 没有变化，所以 dp[i+1][j+1] = min(self, dp[i][j])
//
// 如果放入序列 y，前提是 dp[i][j] < a[i+1]，也就是要满足递增条件.
// 此时序列 y 变化了, x 没有变化. 但是 dp 的含义是: a[i] 一定要是 x 的尾部.
// 所以，x 和 y 需要交换。
// y 成了新的 x，长度是 i-j+1.
// x 成了新的 y, 更新末尾元素的最小值: dp[i+1][i-j+1] = min(self, a[i])
//
// 最终是否可以成功切分，取决于 dp[n][n/2] 是否有被设置过
//
// dp[1][1] 需要初始化为 -1, 因为此时另一个序列不存在
bool check(int n) {
    memset(dp, 0x3f, sizeof dp);

    dp[1][1] = -1;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= std::min(n / 2, i); j++) {
            if (a[i - 1] < a[i])
                dp[i + 1][j + 1] = std::min(dp[i + 1][j + 1], dp[i][j]);
            if (dp[i][j] < a[i])
                dp[i + 1][i - j + 1] = std::min(dp[i + 1][i - j + 1], a[i - 1]);
        }
    }

    return dp[n][n / 2] != inf;
}

int main(void) {
    // 多组测试数据
    while (1) {
        // 输入
        int n;
        cin >> n;
        if (cin.eof()) break;

        // 输入数组
        for (int j = 0; j < n; j++) cin >> a[j];
        getchar();

        // 调用
        if (check(n))
            cout << "Yes!" << endl;
        else
            cout << "No!" << endl;
    }
    return 0;
}
