// https://leetcode.cn/problems/find-k-pairs-with-smallest-sums

#include <queue>
#include <utility>
#include <vector>
using namespace std;
class Solution {
    using P = pair<int, int>;  // i, j
   public:
    // 时间复杂度 klog(min(m, n))
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,
                                       int k) {
        vector<vector<int>> ans;

        // 小根堆, 和更小的在上面
        auto cmp = [&](const P& a, const P& b) {
            return nums1[a.first] + nums2[a.second] >
                   nums1[b.first] + nums2[b.second];
        };
        priority_queue<P, vector<P>, decltype(cmp)> q(cmp);

        // +-----> 增大
        // | a0+b0  a0+b1 a0+b2 ...
        // | a1+b0  a1+b1 a1+b2
        // | a2+b0  a2+b1 a2+b2
        // V ...
        // 增大

        // 先把每行的行头 {i, 0} 放入堆中
        for (int i = 0; i < nums1.size(); i++) q.push({i, 0});

        // 置换 K 次
        while (k-- && !q.empty()) {
            auto [i, j] = q.top();
            ans.push_back({nums1[i], nums2[j]});
            q.pop();
            if (j + 1 < nums2.size()) q.push({i, j + 1});
        }
        return ans;
    }
};
