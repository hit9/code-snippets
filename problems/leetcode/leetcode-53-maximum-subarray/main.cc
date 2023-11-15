#include <vector>
using namespace std;

// 思路:
// 1. 先求前缀和数组 sums, 第一项是 0
// 2. 再计算每个 sum[i] 左侧 (包括位置 i) 的最小值的位置 min_pos[i]
//    从左向右找 min 的过程可以做到这一点.
// 3. 逆向遍历 sums 找到最大的 sums[i] - sums[min_pos[i]] 即可

class Solution {
   public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        // 前缀和数组，第0项是 0
        vector<int> sums(n + 1, 0);
        for (int i = 1; i < n + 1; i++) sums[i] = sums[i - 1] + nums[i - 1];

        // min_pos[i] 是 i 以左侧 (包括位置 i) 最小值的位置
        vector<int> min_pos(n + 1, 0);
        min_pos[0] = 0;
        for (int i = 1; i < n + 1; i++) {
            if (sums[i] < sums[min_pos[i - 1]])
                min_pos[i] = i;
            else
                min_pos[i] = min_pos[i - 1];
        }

        // 从右向左找 max(sums[i] - sums[min_pos[i]])
        int ans = INT_MIN;

        for (int i = n; i >= 1; i--) {
            int j = min_pos[i];
            // j == i 的情况说明 i 是当前已左最小的值了,
            // 说明 i 左侧都是递减的，返回当前值本身
            ans = std::max(ans, j == i ? nums[i-1] : (sums[i] - sums[j]));
        }

        return ans;
    }
};
