// 维护区间和的树状数组

#include <vector>

using namespace std;

namespace bit {
// 树状数组，维护值域 [1..n] 上的区间和
// 空间大小 n+1
class BIT {
   private:
    int n;
    // c[x] 存储 [x-lowbit(x)+1,x] 区间上的和
    vector<int> c;

   public:
    explicit BIT(int n) : n(n), c(vector<int>(n + 1, 0)) {}
    int lowbit(int x) { return x & -x; }

    // 查询 [1..x] 区间维护的和
    int ask(int x) {
        int ans = 0;
        for (; x; x -= lowbit(x)) ans += c[x];
        return ans;
    }
    // 查询 [l..r] 区间维护的和
    // 和运算可逆操作
    int ask(int l, int r) { return ask(r) - ask(l - 1); }

    // 单点增加
    void add(int x, int v) {
        for (; x <= n; x += lowbit(x)) c[x] += v;
    }
};
}  // namespace bit
