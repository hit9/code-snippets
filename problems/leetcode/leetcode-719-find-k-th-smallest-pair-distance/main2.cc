#include <queue>
#include <utility>
#include <vector>
using namespace std;
using P = pair<int, int>;  // a,b
class Solution {
   public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        // 小顶堆
        auto cmp = [&](const P& x, const P& y) {
            return nums[x.second] - nums[x.first] >
                   nums[y.second] - nums[y.first];
        };
        priority_queue<P, vector<P>, decltype(cmp)> q(cmp);
        // {i,i+1} 入队
        for (int i = 0; i < n - 1; i++) q.push({i, i + 1});

        // 置换 k 次
        int ans = 0;

        while (k-- && !q.empty()) {
            auto [a, b] = q.top();
            q.pop();
            ans = nums[b] - nums[a];
            if (b + 1 < n) q.push({a, b + 1});
        }
        return ans;
    }
};
