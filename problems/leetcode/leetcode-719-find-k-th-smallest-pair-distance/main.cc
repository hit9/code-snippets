// https://leetcode.cn/problems/find-k-th-smallest-pair-distance
// 719. 找出第 K 小的数对距离


#include <algorithm>
#include <vector>
using namespace std;
class Solution {
   public:
    // 计算有序数组 nums 中距离不大于 x 的距离对的个数
    // 相当于 对于数组的每个元素 y 找 <= y+x  的右界
    int count(const vector<int>& nums, int x) {
        int n = nums.size();
        int c = 0;
        for (int i = 0; i < n; i++) {
            int l = 0;
            int r = n - 1;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (nums[mid] <= nums[i] + x)
                    l = mid;
                else
                    r = mid - 1;
            }
            if (l > i) c += l - i;
        }
        return c;
    }

    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int l = 0;
        int r = nums[n - 1] - nums[0];

        while (l < r) {
            // 找满足 count(x) >=k 的左界
            int mid = (l + r) >> 1;
            if (count(nums, mid) >= k)
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }
};
