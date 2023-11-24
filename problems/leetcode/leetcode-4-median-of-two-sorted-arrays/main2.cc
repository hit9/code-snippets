// https://writings.sh/post/binary-search#例子寻找两个正序数组的中位数

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.empty() && nums2.empty()) return 0;

        int n = nums1.size();
        int m = nums2.size();

        // 确保 nums1 是更小的那个
        if (n > m) return findMedianSortedArrays(nums2, nums1);

        int k = (n + m + 1) / 2;

        int l = 0, r = n;
        int L1, L2, R1, R2;

        while (l <= r) {
            int c1 = (l + r) >> 1;
            int c2 = k - c1;

            // 注意判断分割是否有效
            L1 = (c1 >= 1 && c1 <= n) ? nums1[c1 - 1] : INT_MIN;
            R1 = (c1 <= n - 1 && c1 >= 0) ? nums1[c1] : INT_MAX;
            L2 = (c2 >= 1 && c2 <= m) ? nums2[c2 - 1] : INT_MIN;
            R2 = (c2 <= m - 1 && c2 >= 0) ? nums2[c2] : INT_MAX;

            if (L1 > R2) r = c1 - 1;
            else if (L2 > R1) l = c1 + 1;
            else break;
        }

        // 奇数情况
        if ((m + n) & 1) return max(L1, L2);
        // 偶数情况
        return (max(L1, L2) + min(R1, R2)) / 2.0;
    }
};

int main(void) {
    vector<int> nums1{1, 2, 3, 5, 6};
    vector<int> nums2{4};
    Solution s;
    cout << s.findMedianSortedArrays(nums1, nums2) << endl;
    return 0;
}
