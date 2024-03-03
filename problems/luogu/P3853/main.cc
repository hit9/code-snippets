#include <cstdio>
#include <cstring>

using namespace std;

int L, n, k;
int a[100001];  // 已经设置的路标, 下标从1开始
int diff[100002];  // 预处理差分数组 diff[i] = a[i]-a[i-1], diff[n+1] = L-a[n]

// 如果要求最大间隔是 x 的话, 需要至少设置多少个路标?
// count 具有二段性, 更进一步地, x 越大, 返回值不升; 不升的.
int count(int x) {
    int ans = 0;
    for (int i = 1; i <= n + 1; i++) {
        ans += diff[i] / x;
        if (diff[i] > 0 && diff[i] % x == 0) --ans;  // 正好整除的情况
    }
    return ans;
}

// 二分枚举
int solve() {
    // 预处理差分数组
    memset(diff, 0, sizeof diff);
    for (int i = 1; i <= n; i++) diff[i] = a[i] - a[i - 1];
    diff[n + 1] = L - a[n];

    // 二分答案, 求满足 count(x) <= k 的左界
    // 转化为 check 不降函数求 check(x) >= L - k 的左界
    auto f = [&](int x) { return L - count(x); };

    int l = 1, r = L;
    while (l < r) {
        int m = (l + r) >> 1;
        if (f(m) >= L - k)
            r = m;
        else
            l = m + 1;
    }
    return l;
}

int main(void) {
    scanf("%d%d%d", &L, &n, &k);
    int m = n, i = 0;
    memset(a, 0, sizeof a);
    while (m--) scanf("%d", &a[++i]);
    printf("%d\n", solve());
    return 0;
}
