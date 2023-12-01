// 维护前缀区间最大值的树状数组

#include <vector>

using namespace std;

// 树状数组，维护值域 [1..n] 上的最值
// 空间大小 n+1
class BIT {
   private:
    int n;
    // c[x] 存储 [x-lowbit(x)+1,x] 区间上的最值
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
    // 单点修改
    void update(int x, int v) {
        for (; x <= n; x += lowbit(x)) c[x] = std::max(c[x], v);
    }
};
