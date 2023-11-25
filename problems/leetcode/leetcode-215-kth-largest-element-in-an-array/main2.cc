#include <queue>
#include <vector>

// 小顶堆 nlogk

using namespace std;

class Solution {
   public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> q;
        for (int i = 0; i < k; i++) q.push(nums[i]);
        // 置换
        for (int i = k; i < nums.size(); i++) {
            q.push(nums[i]);
            q.pop();
        }
        return q.top();
    }
};
