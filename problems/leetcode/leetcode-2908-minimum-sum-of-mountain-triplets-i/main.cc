#include <vector>
using namespace std;
const int inf = 0x3f3f3f3f;
class Solution {
   public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> L(n, inf);  // L[i] 是 nums[i] 左边的最小值
        vector<int> R(n, inf);  // R[i] 是 nums[i] 右边的最小值
        for (int i = 1; i < n; i++) L[i] = min(L[i-1], nums[i - 1]);
        for (int i = n - 2; i >= 0; i--) R[i] = min(R[i+1], nums[i + 1]);
        // 枚举中间的最大的 j
        int s = inf;
        for (int i = 1; i < n - 1; i++) {
            // 确保中间的更大才更新
            if (L[i] < nums[i] && R[i] < nums[i])
                s = min(s, nums[i] + L[i] + R[i]);
        }
        if (s >= inf) return -1;
        return s;
    }
};
