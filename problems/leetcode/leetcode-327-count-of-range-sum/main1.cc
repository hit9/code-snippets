#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// CDQ 做法

using ll = long long;

struct P {
    int idx;
    ll sum;
};

bool cmp_sum(const P& a, const P& b) { return a.sum < b.sum; }
bool cmp_idx(const P& a, const P& b) { return a.idx < b.idx; }

class Solution {
   public:
    // cdq 处理 [k+1, j] 上的答案，其中 1<=k<j<n
    // 也就是不包含左端点是 0 的情况, 区间和可表达为 sums[j]-sums[k]
    // 时间复杂度 (logn)^2
    void cdq(vector<P>& a, int start, int end, int lower, int upper, int& ans) {
        if (start >= end) return;
        int mid = (start + end) >> 1;

        // 先处理左边
        cdq(a, start, mid, lower, upper, ans);

        // 左边和右边分别排序
        sort(a.begin() + start, a.begin() + mid + 1, cmp_sum);
        sort(a.begin() + mid + 1, a.begin() + end + 1, cmp_sum);

        // 计算左边对右边的贡献
        // 拆两个任务:
        // cnt1. y-x <= lower-1 的数量
        // cnt2. y-x <= upper 的数量
        // 再求计数差
        int cnt1 = count(a, start, end, mid, lower - 1);
        int cnt2 = count(a, start, end, mid, upper);
        ans += cnt2 - cnt1;

        // 恢复右边秩序
        sort(a.begin() + mid + 1, a.begin() + end + 1, cmp_idx);
        // 再处理右边
        cdq(a, mid + 1, end, lower, upper, ans);
    }
    // 左右两边已经有序的情况下
    // 计算差值 (右边y - 左边x) <= upper 的对的数量
    // 相当于：对于右边任一个 y ，找左边 x >= y - upper 的数量
    // 因为两边都已经排序, 此时 x 不满足时不必要回退：
    // 因为下一个 y 会导致更高的下界 (y-upper), x 只能前进
    // 因此 O(n)
    ll count(const vector<P>& a, int start, int end, int mid, ll upper) {
        int k = start, j = mid + 1;
        ll cnt = 0;
        while (j <= end) {
            ll v = a[j].sum - upper;  // a[j].sum 是 y
            while (k <= mid) {
                if (a[k].sum >= v) {  // a[k].sum 是 x
                    // [k,mid] 上的 x 都更大，所有满足
                    cnt += (mid - k + 1);
                    break;
                }
                k++;
            }
            j++;
        }
        return cnt;
    }

    int countRangeSum(const vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        // 先计算前缀和 nums[0..i] => sums[i]
        vector<ll> sums(n, 0);
        sums[0] = nums[0];
        for (int i = 1; i < n; i++) sums[i] = sums[i - 1] + nums[i];

        int ans = 0;

        // 特判: 0 开头的区间
        for (ll s : sums)
            if (s >= lower && s <= upper) ans++;

        // CDQ
        vector<P> a(n);
        for (int i = 0; i < n; i++) a[i] = {i, sums[i]};

        cdq(a, 0, n - 1, lower, upper, ans);

        return ans;
    }
};

int main(void) {
    Solution s;
    vector<int> nums{-2, 5, -1, 2, 3, 1, 0};
    cout << s.countRangeSum(nums, -2, 5) << endl;
    return 0;
}
