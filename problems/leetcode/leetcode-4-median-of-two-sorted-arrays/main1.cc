#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 二分判定法

class Solution {
   public:
    // 计算两个数组中不大于 x 的元素的数量
    // 采用二分法, 查每个数组 <= x 的上界, 再求和
    int count(const vector<int>& nums1, const vector<int>& nums2, int x) {
        int ans = 0;
        if (!nums1.empty() && nums1[0] <= x) {
            // upper_bound 返回严格 > x 的第一个元素
            ans += (upper_bound(nums1.begin(), nums1.end(), x) - nums1.begin());
        }
        if (!nums2.empty() && nums2[0] <= x) {
            ans += (upper_bound(nums2.begin(), nums2.end(), x) - nums2.begin());
        }
        return ans;
    }

    int topk(const vector<int>& nums1, const vector<int>& nums2, int k) {
        // 最小 和 最大可行解
        int l = std::min(nums1.empty() ? INT_MAX : nums1[0],
                         nums2.empty() ? INT_MAX : nums2[0]);
        int r = std::max(nums1.empty() ? INT_MIN : nums1[nums1.size() - 1],
                         nums2.empty() ? INT_MIN : nums2[nums2.size() - 1]);

        // 二分判定, 求满足 count(mid) >= k 的下界
        while (l < r) {
            int mid = (l + r) >> 1;
            if (count(nums1, nums2, mid) >= k)
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.empty() && nums2.empty()) return 0;

        // 中位数是 top k=(n+1)/2 问题
        int n = nums1.size();
        int m = nums2.size();
        int q = m + n;

        if (q & 1) {
            // 奇数, 取最中间的元素 (m+n+1)/2
            return topk(nums1, nums2, (q + 1) / 2);
        } else {
            // 偶数, 取中间两个的平均值
            auto a = topk(nums1, nums2, q / 2);
            auto b = topk(nums1, nums2, q / 2 + 1);
            return (a + b) / 2.0;
        }
    }
};

int main(void) {
    Solution s;
    vector<int> nums1{1, 3};
    vector<int> nums2{2};
    cout << s.findMedianSortedArrays(nums1, nums2) << endl;
    return 0;
}
