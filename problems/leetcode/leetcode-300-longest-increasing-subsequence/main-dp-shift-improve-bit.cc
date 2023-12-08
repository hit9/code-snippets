// LIS 问题的树状数组优化 DP 转移

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 树状数组，取 max
// 维护范围 <= x 的 dp max 值
// 值域范围 [1..n]
class BIT {
   private:
    int n;
    vector<int> c;

   public:
    explicit BIT(int n) : n(n), c(vector<int>(n + 1, 0)) {}
    int ask(int x) {
        int ans = 0;
        for (; x; x -= x & -x) ans = std::max(c[x], ans);
        return ans;
    }
    void update(int x, int v) {
        for (; x <= n; x += x & -x) c[x] = std::max(c[x], v);
    }
};

class Solution {
   public:
    // 原地离散化值到 1~m, 返回值域最大值m
    int discrete(vector<int>& nums) {
        // 离散化: 拷贝后，排序+去重
        vector<int> r(nums.begin(), nums.end());
        sort(r.begin(), r.end());

        // 去重
        int m = unique(r.begin(), r.end()) - r.begin();

        // 用离散化后的数据重写 nums
        for (int i = 0; i < nums.size(); i++) {
            auto low = lower_bound(r.begin(), r.begin() + m, nums[i]);
            nums[i] = low - r.begin() + 1;  //  映射到 [1..m];
        }
        return m;
    }
    int lengthOfLIS(vector<int>& nums) {
        int m = discrete(nums);

        // 树状数组求解 dp
        // dp 数组虽然没有写出，但是是理论依据
        // dp[x] 的含义是以值 `x` 结尾的能形成的 LIS 的长度
        // dp 的递推逻辑是:
        //     dp[x] = max(dp[x], dp[v] + 1), 其中 v < x
        // 所以可以用树状数组维护 dp 数组的最值
        // 值域范围 1~m, 树状数组需要空出第 0 号槽位
        BIT b(m);
        for (int i = 0; i < nums.size(); i++) {
            auto x = nums[i];
            // 先取出 <= x-1 的 max dp 值
            // 更新 <= x 的 max dp 值
            b.update(x, b.ask(x - 1) + 1);
        }
        return b.ask(m);
    }
};

int main(void) {
    vector<int> nums{0, 1, 0, 3, 2, 3};
    Solution s;
    cout << s.lengthOfLIS(nums) << endl;
    return 0;
}
