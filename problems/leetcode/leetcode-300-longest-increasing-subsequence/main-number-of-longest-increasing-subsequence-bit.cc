// https://leetcode.cn/problems/number-of-longest-increasing-subsequence/
// 673. 最长递增子序列的个数
// 树状数组解法

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct P {
    int f, g;  // LIS 的长度 f 和个数 g
};

class BIT {
   private:
    int n;
    vector<P> c;

   public:
    explicit BIT(int n) : n(n), c(vector<P>(n + 1)) {}
    int lowbit(int x) { return x & -x; }
    // c[x].f 维护区间 [x-lowbit(x)+1, x] 上的 lis 长度最值
    // c[x].g 维护区间 [x-lowbit(x)+1, x] 上的 lis 长度为 f 的个数
    void update(int x, const P& p) {
        for (; x <= n; x += lowbit(x)) {
            // 小区间内的最长 LIS 长度即将更换，重置计数
            if (c[x].f < p.f) c[x].g = 0;
            // 一定是 p.f 取胜的情况，计算计数
            // 否则小区间管辖的最长 LIS 长度不变，个数也不用动
            if (c[x].f <= p.f) c[x].g += p.g;
            c[x].f = max(c[x].f, p.f);
        }
    }
    // f 是 [1,x] 的最大 lis 长度
    // g 是 [1,x] 的长度为 f 的个数
    P ask(int x) {
        int f = 0, g = 0;
        for (; x; x -= lowbit(x)) {
            // f 即将更换，重置计数
            if (f < c[x].f) g = 0;
            // c[x].f 必然取胜的情况，统计其计数
            if (f <= c[x].f) g += c[x].g;
            f = max(f, c[x].f);
        }
        return {f, g};
    }
};

class Solution {
   public:
    // 原地离散化到值域 [1,m]
    int discrete(vector<int>& a) {
        vector<int> p(a.begin(), a.end());
        sort(p.begin(), p.end());
        int m = unique(p.begin(), p.end()) - p.begin();
        for (auto& x : a)
            x = lower_bound(p.begin(), p.begin() + m, x) - p.begin() + 1;
        return m;
    }
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        // 原地离散化
        int m = discrete(nums);

        BIT b(m);
        for (auto x : nums) {
            // 查询 < x 的最长 LIS 的长度 f
            // 以及长度是 f 的个数 g
            auto p = b.ask(x - 1);
            // f(x) ← max f(v) + 1, for v < x;
            b.update(x, {p.f + 1, max(p.g, 1)});
        }
        return b.ask(m).g;
    }
};

int main(void) {
    vector<int> nums{2, 7, 4, 1, 5, 3, 4, 7, 6, 8};
    Solution s;
    cout << s.findNumberOfLIS(nums) << endl;
    return 0;
}
