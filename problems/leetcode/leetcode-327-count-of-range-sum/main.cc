#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

// 先求前缀和
// 从右向左枚举 i
// 区间和 S[i, j] = Sum[j] - Sum[i-1]
// 要 S 在 [lower, upper] 内
// 那么就是找右侧的满足以下条件的 j 的个数
// lower + Sum[i-1] <= Sum[j] <= upper + Sum[i-1]
// 用 sorted map 维护已经扫描过的 Sum[j] -->  会超时..
// 用 BIT 树状数组来维护值域计数
// 特殊的 i == 0 时，两边取 Sum[i-1] 钦定为 0

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

using ll = long long;

class Solution {
   public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        // 先计算前缀和 nums[0..i] => sums[i]
        ll sums[n];
        sums[0] = nums[0];
        for (int i = 1; i < n; i++) sums[i] = sums[i - 1] + nums[i];

        // sum 离散化，用离散化后的数据来代表计数
        // 离散化技巧: 也要把 x+lower 和 x+upper 放进去
        set<ll> st;
        for (auto x : sums) {
            st.insert(x);
            st.insert(x + lower);
            st.insert(x + upper);
        }
        st.insert(0 + lower);
        st.insert(0 + upper);

        // 离散化前的数据值 => 映射到具体的大小
        // 用树状数组的话，映射到 1 起始的值域
        unordered_map<ll, int> mp;
        for (auto x : st) mp[x] = mp.size() + 1;

        BIT b(mp.size() + 1);

        int ans = 0;

        for (int i = n - 1; i >= 0; i--) {
            // i 可以等于 j，所以先计数，后查询
            b.add(mp[sums[i]], 1);  // 计数+1

            ll k = (i == 0 ? 0 : sums[i - 1]);
            ll l = lower + k, r = upper + k;

            // 求 [l, r] 内的计数
            // 转化为 count[1,r] - count[1, l-1] 的问题
            int c = b.ask(mp[r]) - b.ask(mp[l] - 1);
            ans += c;
        }
        return ans;
    }
};
