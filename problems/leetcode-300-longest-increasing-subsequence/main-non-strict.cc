// 如果求解非严格递增的子序列长度呢?
//
// 例如:
// 输入 nums = [10,9,2,5,2,3,7,101,18]
// 输: 5 (序列是 2,2,3,7,18)

// 思路:
// 排序，按索引转换为最长严格递增
// 仍然可以走 nlog(n)

#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;
class Solution {
   public:
    // 传统 LIS 问题
    int originalLIS(vector<int>& nums) {
        vector<int> p{nums[0]};

        for (int i = 1; i < nums.size(); i++) {
            if (auto num = nums[i]; num > p.back())
                p.push_back(num);
            else {
                auto j = lower_bound(p.begin(), p.end(), num);
                *j = num;
            }
        }
        return p.size();
    }

    // 非严格递增 LIS 问题
    int looseLIS(vector<int>& nums) {
        // 制作一个下标数组
        vector<int> arr;
        for (int i = 0; i < nums.size(); i++) arr.push_back(i);
        // 按数值排序. 如果数值相等，因为允许非严格递增, 则按下标正序
        sort(arr.begin(), arr.end(), [&](const auto& a, const auto& b) {
            return nums[a] < nums[b] || (nums[a] == nums[b] && a < b);
        });
        // 然后求下标数组的最长严格递增序列
        return originalLIS(arr);
    }
};

int main(void) {
    Solution s;

    vector<int> nums1{10, 9, 2, 5, 2, 3, 7, 101, 18};
    assert(s.looseLIS(nums1) == 5);

    vector<int> nums2{10, 9, 2, 5, 2, 3, 7, 101, 7, 18};
    assert(s.looseLIS(nums2) == 6);

    vector<int> nums3{0, 1, 0, 2, 3, 2, 3};
    assert(s.looseLIS(nums3) == 5);

    vector<int> nums4{7, 7, 7, 7, 7, 7, 7};
    assert(s.looseLIS(nums4) == nums4.size());

    vector<int> nums5{2, 4, 2, 7, 3, 6, 3, 8, 3, 5, 6};
    assert(s.looseLIS(nums5) == 7);
    return 0;
}
