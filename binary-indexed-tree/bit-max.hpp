// 维护区间最大值的树状数组

#include <vector>

namespace bit {
using namespace std;

// 树状数组，维护值域 [1..n] 上的区间最值
// 空间大小 n+1
class BIT1 {
   private:
    int n;
    // c[x] 存储 [x-lowbit(x)+1,x] 区间上的最值
    vector<int> c;
    // a 是原数组, 跟进每个位置的最新值
    vector<int> a;

   public:
    explicit BIT1(int n)
        : n(n), c(vector<int>(n + 1, 0)), a(vector<int>(n + 1, 0)) {}

    int lowbit(int x) { return x & -x; }

    // 查询 [l..r] 区间维护的最大值
    int ask(int l, int r) {
        // 从 r 向前枚举, 直到 l
        int ans = 0;

        while (r >= l) {
            // 注意 c[r] 负责的区间长度是 lowbit(r)
            // 当区间左端点 r-lowbit(r)+r > l , 即没有抵达左边界 l
            // 的时候，可以跳着走
            for (; r - lowbit(r) + 1 > l; r -= lowbit(r))
                ans = std::max(c[r], ans);
            // 当 r 和 l 之间没有 r 的子节点的时候，退化成枚举
            // 枚举一次，然后继续尝试跳
            ans = std::max(a[r--], ans);
        }

        return ans;
    }
    // 单点修改
    void update(int x, int v) {
        a[x] = v;  // 并更新原数组
        for (; x <= n; x += lowbit(x)) c[x] = max(c[x], v);
    }
};
}  // namespace bit
