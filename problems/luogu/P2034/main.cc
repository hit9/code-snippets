#include <algorithm>
#include <cstdio>
#include <deque>
using namespace std;
using ll = long long;
const int N = 100005;

ll a[N], f[N], s[N], g[N];
int n, k;

ll solve() {
    // 计算前缀和
    s[0] = 0;
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];

    f[0] = 0;
    // g[i] = f[i-1] - s[i]
    g[0] = 0;

    // 维护 [i-k, i-1] 区间上的 g 的单调递减队列, 存储下标
    deque<int> q;

    for (int i = 1; i <= n; i++) {
        // 维护队头
        while (!q.empty() && q.front() + k < i) q.pop_front();
        // 推导 dp
        if (i <= k)  // 前 k 个的答案就是前缀和
            f[i] = s[i];
        else {                // 两种情况
            f[i] = f[i - 1];  // 不选 a[i]
            // 选 a[i],但是要排除 [i-k,i-1] 内的一个 j
            if (!q.empty()) f[i] = max(f[i], g[q.front()] + s[i]);
        }
        // 维护队尾
        g[i] = f[i - 1] - s[i];
        while (!q.empty() && g[q.back()] < g[i]) q.pop_back();
        q.push_back(i);
    }
    return f[n];
}

int main(void) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    printf("%lld", solve());
    return 0;
}
