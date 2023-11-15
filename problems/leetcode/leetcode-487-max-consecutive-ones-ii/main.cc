// https://leetcode.cn/problems/max-consecutive-ones-ii/
// 581. 最短无序连续子数组

#include <deque>
#include <vector>
using namespace std;
class Solution {
   public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        deque<int> q;
        bool has_zero = false;
        int m = 0;
        for (auto v : nums) {
            if (v == 0) {
                if (has_zero) {
                    while (!q.empty() && q.front() != 0) q.pop_front();
                    q.pop_front();  // 弹出0
                } else              // 即将加入 0
                    has_zero = true;
            }
            q.push_back(v);

            if (q.size() > m) m = q.size();
        }
        return m;
    }
};
