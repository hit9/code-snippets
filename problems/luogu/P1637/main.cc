
#include <iostream>
#include <vector>

using namespace std;

class BIT {
   private:
    int n;
    vector<int> c;

   public:
    explicit BIT(int n) : n(n), c(vector<int>(n + 1, 0)) {}
    inline int lowbit(int x) { return x & -x; }
    void add(int x, int d) {
        for (; x <= n; x += lowbit(x)) c[x] += d;
    }
    int ask(int x) {
        int ans = 0;
        for (; x; x -= lowbit(x)) ans += c[x];
        return ans;
    }
};

const int N = 100009;
using ull = unsigned long long;

ull solve(vector<int>& a, int n) {
    // 从左到右记录左侧求 < x 的数量
    BIT p(N);
    vector<int> ap(n + 1);
    for (int i = 1; i <= n; i++) {
        ap[i] = p.ask(a[i] - 1);  // [1, x-1] 上的计数和
        p.add(a[i], 1);
    }

    // 从右到左记录右侧求 > x 的数量
    BIT q(N);
    vector<int> aq(n + 1);
    for (int i = n; i >= 1; i--) {
        aq[i] = q.ask(N) - q.ask(a[i]);  // [x+1, N] 上的计数和
        q.add(a[i], 1);
    }

    // 考虑中间的 j
    // 三元上升的数量就是, 左侧小的数量 乘以 右侧大的数量 之和
    ull ans = 0;

    for (int i = 1; i < n; i++) {
        ans += (ull)ap[i] * (ull)aq[i];
    }

    return ans;
}

int main(void) {
    int n;
    cin >> n;
    getchar();
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    cout << solve(a, n) << endl;
    return 0;
}
