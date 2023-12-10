#include <deque>
#include <iostream>
#include <vector>

using namespace std;

using P = pair<int, int>;  // value, index
auto cmp_value(const P& x, const P& y) { return x.first < y.first; }
auto cmp_index(const P& x, const P& y) { return x.second < y.second; }

class Solution {
   public:
    // [start, end]
    void cdq(vector<int>& dp, vector<P>& a, int start, int end, int k) {
        if (end <= start) return;

        int mid = (start + end) >> 1;

        // 分治左边 [start, mid]
        cdq(dp, a, start, mid, k);

        // 左右分别按值有序, 然后计算左边对右边的贡献
        sort(a.begin() + start, a.begin() + mid + 1, cmp_value);
        sort(a.begin() + mid + 1, a.begin() + end + 1, cmp_value);

        // 对右边的每个 i, 找到左边值比它小的 j 的最大的 dp 值
        // 因为已经按值有序，所以 j 不必回溯
        // 采用单调队列来维护区间 dp 最值
        // 此部分的总均摊时间复杂度是 n

        int i = mid + 1;
        int j = start;
        deque<int> q;  // 维护最大值的单调递减队列, 存储下标
        while (i <= end) {
            while (j <= mid && a[j].first < a[i].first) {
                // 维护右端, 弹出比 a[i] 的 dp 值小的
                while (!q.empty() && dp[a[q.back()].second] < dp[a[j].second])
                    q.pop_back();
                // 加入 a[j]
                q.push_back(j++);

                // 维护左端: 弹出左端已经脱离 k 限制的
                while (!q.empty() && a[q.front()].first + k < a[i].first)
                    q.pop_front();
            }
            while (!q.empty() && a[q.front()].first + k < a[i].first)
                q.pop_front();
            int ma = q.empty() ? 0 : dp[a[q.front()].second];
            dp[a[i].second] = std::max(dp[a[i].second], ma + 1);
            i++;
        }

        // 恢复秩序, 其实左边没有必要恢复
        // sort(a.begin() + start, a.begin() + mid + 1, cmp_index);
        sort(a.begin() + mid + 1, a.begin() + end + 1, cmp_index);

        // 分治右边 [mid+1, end]
        cdq(dp, a, mid + 1, end, k);
    }
    int lengthOfLIS(vector<int>& nums, int k) {
        int n = nums.size();
        vector<P> a(n);
        for (int i = 0; i < n; i++) a[i] = {nums[i], i};
        vector<int> dp(n, 1);
        cdq(dp, a, 0, n - 1, k);
        return *max_element(dp.begin(), dp.end());
    }
};

int main(void) {
    Solution s;
    vector<int> nums{6, 20, 16, 20, 13, 18, 9};
    cout << s.lengthOfLIS(nums, 5) << endl;
    return 0;
}
