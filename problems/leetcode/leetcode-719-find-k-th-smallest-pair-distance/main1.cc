
#include <algorithm>
#include <vector>
using namespace std;
class Solution {
   public:
    // 计算有序数组 nums 中距离不大于 x 的距离对的个数
    // 滑窗思路：因为数组是已排序的，所以越靠右，窗尾对窗头的差值越大
    // 超过阈值后，就收缩窗头
    int count(const vector<int>& nums, int x) {
        int n = nums.size();
        int L = 0, R = 1;
        int c = 0;
        while (R < n) {
            while (L < R && nums[R] - nums[L] > x) L++;
            // 以 R 为大值的距离对个数
            // 注意 R 不可等于 L
            c += R - L;
            R++;
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
