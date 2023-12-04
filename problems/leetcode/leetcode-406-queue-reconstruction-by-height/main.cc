// https://leetcode.cn/problems/queue-reconstruction-by-height

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [&](const auto& a, const auto& b) {
            return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);
        });

        // 不断在排名位置处插入
        vector<vector<int>> q;

        for (auto& x : people) {
            q.insert(q.begin() + x[1], x);
        }
        return q;
    }
};
