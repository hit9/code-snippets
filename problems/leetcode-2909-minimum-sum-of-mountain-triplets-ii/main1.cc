// https://leetcode.cn/problems/minimum-sum-of-mountain-triplets-ii

#include <vector>
using namespace std;
class Solution {
   public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        // L[i] 表示位置 i 左侧的最小值, 不含 nums[i]
        vector<int> L(n, INT_MAX);
        // R[i] 表示位置 i 右侧的最小值, 不含 nums[i]
        vector<int> R(n, INT_MAX);

        for (int i = 1; i < nums.size(); i++)
            L[i] = std::min(L[i - 1], nums[i - 1]);
        for (int j = nums.size() - 2; j >= 0; j--)
            R[j] = std::min(R[j + 1], nums[j + 1]);

        // 考虑每个可能的中间的山峰元素
        int sum = INT_MAX;  // 追踪最小和
        for (int i = 1; i < nums.size() - 1; i++) {
            auto left = L[i];
            auto right = R[i];
            if (left < nums[i] && nums[i] > right)
                sum = std::min(L[i] + R[i] + nums[i], sum);
        }
        if (sum == INT_MAX) return -1;
        return sum;
    }
};
