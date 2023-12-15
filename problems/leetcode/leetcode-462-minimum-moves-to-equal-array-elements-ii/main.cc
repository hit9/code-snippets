// https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/

#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;
class Solution {
   public:
    int topk(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> q;
        for (int i = 0; i < k; i++) q.push(nums[i]);
        // 置换
        for (int i = k; i < nums.size(); i++) {
            q.push(nums[i]);
            q.pop();
        }
        return q.top();
    }

    int distance(const vector<int>& nums, int target) {
        int ans = 0;
        for (auto x : nums) ans += abs(x - target);
        return ans;
    }

    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        int k = (n + 1) / 2;
        int v1 = topk(nums, k);
        // 奇数
        if (n & 1) return distance(nums, v1);
        // 偶数
        int v2 = topk(nums, k + 1);
        return min(distance(nums, v1), distance(nums, v2));
    }
};
