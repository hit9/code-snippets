#include <numeric>
#include <vector>
using namespace std;
class Solution {
   public:
    // 计算数组 nums 中连续子段和不超过 x 的连续子数组的数目
    // 由于都是正整数，可以通过滑动窗口来实现
    int count(vector<int>& nums, int x) {
        int L = 0, R = 0;
        int n = nums.size();
        int sum = 0;
        int ans = 0;
        while (R < n) {
            // 计算当前窗口内的和
            sum += nums[R];
            while (sum > x && L <= R) {
                // 左侧移进
                sum -= nums[L];
                L++;
            }
            // 当前窗口内所有以 R 结尾的都计数一次
            ans += R - L + 1;
            // 右侧移进
            R++;
        }
        return ans;
    }
    int kthSmallestSubarraySum(vector<int>& nums, int k) {
        // 二分从大到小枚举答案:
        // 对于一个可能的 X, 如果子段和不超过 X 的数目不足 K 个
        // 说明枚举的 X 太小了.
        // 可以用二分的原因在于, 假设正确答案是 Ans, 因为都是正数元素，
        // 对于 >= Ans 的数字 X 而言, 和不超过 X 的子数组数目一定会满足 >=k
        // 所以，要找到恰好满足 count >=k 的左界的那个 X
        int l = *min_element(nums.begin(), nums.end());  // 最小的可能的和
        int r = accumulate(nums.begin(), nums.end(), 0);  // 最大的可能的和
        while (l < r) {
            int x = (l + r) >> 1;
            if (count(nums, x) >= k)
                r = x;
            else
                l = x + 1;
        }
        return l;
    }
};
