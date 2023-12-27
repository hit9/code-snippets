// 受 main.cc CDQ 分治的启发
// CDQ 是: 先分治处理左边、再计算左边对右边的贡献，再恢复右侧秩序继续分治右边
// 其实，计数问题，和顺序关系不那么大，可以把分治处理的顺序调整一下：
// 1. 分治左边、左边排序
// 2. 分治右边、右边排序
// 3. 计算左边对右边的贡献
//
// 这其实就是归并排序，具体来说，分治过程中用一个临时数组 tmp 来跟随归并排序过程
// 时间复杂度可以做到 nlogn

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

class Solution {
   public:
    // 把 a 的两段区间合并到 tmp 数组的 start 位置，同归并排序
    // 假定 start1 更小, end1 最大
    void merge(vector<ll>& a, int start1, int end1, int start2, int end2,
               vector<ll>& tmp, int start) {
        int s1 = start1, e2 = end2, s = start;
        while (start1 <= end1 && start2 <= end2) {
            if (a[start1] <= a[start2])
                tmp[start++] = a[start1++];
            else
                tmp[start++] = a[start2++];
        }
        while (start1 <= end1) tmp[start++] = a[start1++];
        while (start2 <= end2) tmp[start++] = a[start2++];
        // 拷贝回 tmp => a
        while (s1 <= e2) a[s1++] = tmp[s++];
    }

    // dq 处理 [k+1, j] 上的答案，其中 1<=k<j<n
    // 也就是不包含左端点是 0 的情况, 区间和可表达为 sums[j]-sums[k]
    // 时间复杂度 (logn)^2
    void dq(vector<ll>& a, int start, int end, int lower, int upper, int& ans,
            vector<ll>& tmp) {
        if (start >= end) return;
        int mid = (start + end) >> 1;

        // 先处理左边, 并排序
        dq(a, start, mid, lower, upper, ans, tmp);

        // 再处理右边, 并排序
        dq(a, mid + 1, end, lower, upper, ans, tmp);

        // 计算左边对右边的贡献
        // 拆两个任务:
        // cnt1. y-x <= lower-1 的数量
        // cnt2. y-x <= upper 的数量
        // 再求计数差
        int cnt1 = count(a, start, end, mid, lower - 1);
        int cnt2 = count(a, start, end, mid, upper);
        ans += cnt2 - cnt1;

        // 合并排序
        merge(a, start, mid, mid + 1, end, tmp, start);
    }
    // 左右两边已经有序的情况下
    // 计算差值 (右边y - 左边x) <= upper 的对的数量
    // 相当于：对于右边任一个 y ，找左边 x >= y - upper 的数量
    // 因为两边都已经排序, 此时 x 不满足时不必要回退：
    // 因为下一个 y 会导致更高的下界 (y-upper), x 只能前进
    // 因此 O(n)
    ll count(const vector<ll>& a, int start, int end, int mid, ll upper) {
        int k = start, j = mid + 1;
        ll cnt = 0;
        while (j <= end) {
            ll v = a[j] - upper;  // a[j].sum 是 y
            while (k <= mid) {
                if (a[k] >= v) {  // a[k].sum 是 x
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

        // 归并分治
        vector<ll> tmp(n);
        dq(sums, 0, n - 1, lower, upper, ans, tmp);
        return ans;
    }
};

int main(void) {
    Solution s;
    vector<int> nums{-2, 5, -1, 2, 3, 1, 0};
    cout << s.countRangeSum(nums, -2, 5) << endl;
    return 0;
}
