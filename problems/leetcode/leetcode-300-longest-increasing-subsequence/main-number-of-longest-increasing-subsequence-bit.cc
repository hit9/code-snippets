// https://leetcode.cn/problems/number-of-longest-increasing-subsequence/
// 673. 最长递增子序列的个数
// 树状数组解法

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// LIS 的长度 f 和个数 g
struct P {
    int f, g;
};

// 树状数组：维护 <= x 值域上最长 LIS 的长度，以及其个数
// c[x] 维护小区间 [x-lowbit(x)+1, x] 的信息
// f 是此值域小区间上的最大 lis 长度
// g 是此小区间上长度为 f 的 lis 的个数
struct BIT {
    int n;
    vector<P> c;
    explicit BIT(int n) : n(n), c(vector<P>(n + 1)) {}
    int lowbit(int x) { return x & -x; }
    void update(int x, const P& p) {
        for (; x <= n; x += lowbit(x)) {
            // 更新前，预判小区间的 f 是否即将变化
            // c[x].f 肯定会更换，清零计数
            if (c[x].f < p.f) c[x].g = 0;

            // 新的 p.f 必定取胜，添加其计数的贡献
            // 否则，c[x].f 不会变，c[x].g 也无须变化
            if (c[x].f <= p.f) c[x].g += p.g;

            c[x].f = max(c[x].f, p.f);
        }
    }
    P ask(int x) {
        int f = 0, g = 0;
        for (; x; x -= lowbit(x)) {
            // 更新前，预判当前最大的 f 是否更换
            // f 肯定会被换掉，清零计数
            if (f < c[x].f) g = 0;

            // c[x].f 必定取胜，添加其计数到统计值 g
            // 否则 f 不变的时候，此小区间可忽略
            if (f <= c[x].f) g += c[x].g;

            f = max(f, c[x].f);
        }
        return {f, g};
    }
};

class Solution {
   public:
    int discrete(vector<int>& a) {
        vector<int> p(a.begin(), a.end());
        sort(p.begin(), p.end());
        int m = unique(p.begin(), p.end()) - p.begin();
        for (auto& x : a)
            x = lower_bound(p.begin(), p.begin() + m, x) - p.begin() + 1;
        return m;
    }
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size(), m = discrete(nums);
        BIT b(m);
        for (auto x : nums) {
            auto [f, g] = b.ask(x - 1);
            b.update(x, {f + 1, max(g, 1)});
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
