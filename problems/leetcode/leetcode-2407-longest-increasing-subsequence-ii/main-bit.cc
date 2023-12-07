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
            // 注意 c[r] 负责的区间长度是 lowbit(r)
            // 当 r-lowbit(r)+r > l 的时候，可以跳着走
            for (; r - lowbit(r) + 1 > l; r -= lowbit(r))
                ans = std::max(c[r], ans);
            // 当 r 和 l 之间没有 r 的子节点的时候，退化成一个一个枚举
            ans = std::max(a[r--], ans);
        }

        return ans;
    }
    // 单点修改
    void update(int x, int v) {
        a[x] = v;  // 并更新答案数组
        for (; x <= n; x += lowbit(x)) c[x] = max(c[x], v);
    }
};
class Solution {
   public:
    int lengthOfLIS(vector<int>& nums, int k) {
        // 树状数组求解 dp
        auto maxn = *max_element(nums.begin(), nums.end());
        // dp 数组虽然没有写出，但是是理论依据
        // dp 数组的定义: dp 数组的下标是 nums 的值域 x
        // dp[x] 的含义是以值 `x` 结尾的能形成的相隔元素差不超过 k 的 LIS 的长度
        // dp 的递推逻辑是:
        //     dp[x] = max(dp[x], dp[y] + 1)
        //     其中 y 在区间 [x-k, x-1] 内，这样才能形成新的符合要求的 LIS
        //  树状数组 b 维护的是 dp 数组的区间最值
        BIT b(maxn);
        for (int i = 0; i < nums.size(); i++) {
            auto x = nums[i];
            // 先取出 [x-k, x-1] 的 max dp 值
            // 注意 x-k 可能 <= 0, 要至少1
            // 更新 <= x 的 max dp 值
            b.update(x, b.ask(std::max(x - k, 1), x - 1) + 1);
        }
        return b.ask(1, maxn);
    }
};
