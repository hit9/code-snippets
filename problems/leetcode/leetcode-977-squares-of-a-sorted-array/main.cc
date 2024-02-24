#include <vector>
using namespace std;
// 负数部分原地反转，然后和非负部分归并一下，O(n)
class Solution {
   public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        // 找到第一个非负的下标 k
        int k = 0;
        while (k < n && nums[k] < 0) k++;
        // 翻转 [0..k]
        reverse(nums.begin(), nums.begin() + k);
        // 归并 nums[0..k) 和 nums[k..n)
        int start1 = 0, start2 = k;
        int end1 = k - 1, end2 = n - 1;
        int start = 0;
        vector<int> ans(n, 0);
        while (start1 <= end1 && start2 <= end2) {
            if (abs(nums[start1]) < abs(nums[start2])) {
                ans[start++] = nums[start1] * nums[start1];
                start1++;
            } else {
                ans[start++] = nums[start2] * nums[start2];
                start2++;
            }
        }
        while (start1 <= end1) {
            ans[start++] = nums[start1] * nums[start1];
            start1++;
        }
        while (start2 <= end2) {
            ans[start++] = nums[start2] * nums[start2];
            start2++;
        }
        return ans;
    }
};
