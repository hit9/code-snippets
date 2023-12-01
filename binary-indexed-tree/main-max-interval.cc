// 维护区间最大值的树状数组

#include <vector>

using namespace std;

// 树状数组，维护值域 [1..n] 上的区间最值
// 空间大小 n+1
class BIT {
   private:
    int n;
    // c[x] 存储 [x-lowbit(x)+1,x] 区间上的最值
    vector<int> c;
    // a 可以看做原数组, 也就是值 x 处的答案是 a[x]
    vector<int> a;

   public:
    explicit BIT(int n)
        : n(n), c(vector<int>(n + 1, 0)), a(vector<int>(n + 1, 0)) {}

    int lowbit(int x) { return x & -x; }

    // 查询 [l..r] 区间维护的最大值
    int ask(int l, int r) {
        // 从 r 向前枚举, 直到 l
        int ans = 0;
        while (r >= l) {
            // 当 r 和 l 之间没有 r 的子节点的时候，退化成一个一个枚举
            // 注意和以前的答案取最值
            ans = std::max(a[r--], ans);
            // 注意 c[x] 负责的是 [x-lowbit(x)+1, x] 区间
            // 当 x-lowbit(x)+1 > l 的时候，可以利用 BIT 树的性质
            // 直接考虑 [r-lowbit(r)+1, r] 的最值, 而不必一个一个枚举
            for (; r - lowbit(r) + 1 > l; r -= lowbit(r))
                ans = std::max(c[r], ans);
        }
        return ans;
    }
    // 单点修改
    void update(int x, int v) {
        a[x] = v;  // 并更新答案数组
        for (; x <= n; x += lowbit(x)) c[x] = max(c[x], v);
    }
};
