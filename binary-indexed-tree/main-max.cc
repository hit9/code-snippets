// 维护区间最大值的树状数组
//
#include <vector>

using namespace std;

// 树状数组，维护值域 [1..n] 上的区间最值
class BIT {
   private:
    int n;
    vector<int> c;

   public:
    explicit BIT(int n) : n(n), c(vector<int>(n + 1, 0)) {}
    int lowbit(int x) { return x & -x; }
    // 查询 [1..x] 区间维护的最大值
    int ask(int x) {
        int ans = 0;
        for (; x; x -= lowbit(x)) ans = std::max(c[x], ans);
        return ans;
    }
    // 查询 [l..r] 区间维护的最大值
    int ask(int l, int r) {
        // 注意 c[x] 负责的是 [x-lowbit(x)+1, x] 区间
        // 从 r 向前枚举, 直到 l
        int ans = 0;
        while (r >= l) {
            ans = std::max(c[r--], ans);
            // 优化点在于:
            // 前面还有子节点的情况下，可以直接考虑子节点的值，跳着走
            // 最后在 l 到 r 没有 r 的子节点的时候, 再退化到依次枚举
            for (; r - lowbit(r) >= l; r -= lowbit(r))
                ans = std::max(c[r], ans);
        }
        return ans;
    }
    // 单点修改
    void update(int x, int v) {
        for (; x <= n; x += lowbit(x)) c[x] = std::max(c[x], v);
    }
};
