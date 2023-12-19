#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 树状数组的解法
// https://leetcode.cn/problems/count-of-smaller-numbers-after-self/description/

class BIT {
   private:
    int n;
    vector<int> c;

   public:
    explicit BIT(int n) : n(n), c(vector<int>(n + 1, 0)){};
    int lowbit(int x) { return x & -x; }
    void add(int x, int d) {
        for (; x <= n; x += lowbit(x)) c[x] += d;
    }
    int ask(int x) {
        int ans = 0;
        for (; x; x -= lowbit(x)) ans += c[x];
        return ans;
    }
};

class Solution {
   public:
    int disrete(vector<int>& nums) {
        int n = nums.size();
        vector<int> p(nums.begin(), nums.end());
        sort(p.begin(), p.end());
        int m = unique(p.begin(), p.end()) - p.begin();
        for (int i = 0; i < n; i++) {
            // 映射到 [1~m]
            nums[i] =
                lower_bound(p.begin(), p.begin() + m, nums[i]) - p.begin() + 1;
        }
        return m;
    }
    vector<int> countSmaller(vector<int>& nums) {
        // 先离散化
        int m = disrete(nums);
        // 结果数组
        int n = nums.size();
        vector<int> cnt(n, 0);
        // 树状数组，描述 计数的前缀和
        BIT b(m);
        // 从后向前扫描
        for (int i = n - 1; i >= 0; i--) {
            b.add(nums[i], 1);
            cnt[i] = b.ask(nums[i] - 1);  // 查询 [1,x-1] 的计数之和
        }
        return cnt;
    }
};

int main(void) {
    vector<int> nums{5, 2, 6, 1};
    Solution s;
    s.countSmaller(nums);
    auto result = s.countSmaller(nums);
    for (int i = 0; i < result.size(); i++) cout << result[i] << " ";
    cout << endl;
    return 0;
}
