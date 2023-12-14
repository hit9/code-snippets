// 树状数组求逆序对

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ull = unsigned long long;

class BIT {
   private:
    int n;
    vector<int> c;

   public:
    explicit BIT(int n) : n(n), c(vector<int>(n + 1, 0)) {}
    int lowbit(int x) { return x & -x; }
    int ask(int x) {
        int ans = 0;
        for (; x; x -= lowbit(x)) ans += c[x];
        return ans;
    }
    int ask(int l, int r) { return ask(r) - ask(l - 1); }
    void add(int x, int v) {
        for (; x <= n; x += lowbit(x)) c[x] += v;
    }
};

// 原地离散化
int discrete(vector<int>& a, int n) {
    vector<int> p(a.begin(), a.end());
    sort(p.begin(), p.end());
    int m = unique(p.begin() + 1, p.end()) - (p.begin() + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(p.begin() + 1, p.begin() + 1 + m, a[i]) -
               (p.begin() + 1) + 1;  // 映射到 1~m
    }
    return m;
}

ull solve(vector<int>& a, int n) {
    // 离散化，最大值目前是 m
    int m = discrete(a, n);
    // 在值域上，假设 b[x] 维护当前值为 x 的元素的数量
    // 从右向左扫描数组 a，遇到值 x 时
    // 前缀和 sum(b[1,x-1]) 就是所有小于 x 的值的数目
    // 而这些计数来源于历史上扫描其右侧元素而得
    // 所以累加这些计数即可。
    ull ans = 0;
    BIT b(m);
    for (int i = n; i >= 1; i--) {
        b.add(a[i], 1);
        ans += b.ask(a[i] - 1);
    }
    return ans;
}

int main(void) {
    int n;
    cin >> n;
    getchar();

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    getchar();

    cout << solve(a, n) << endl;
    return 0;
}
