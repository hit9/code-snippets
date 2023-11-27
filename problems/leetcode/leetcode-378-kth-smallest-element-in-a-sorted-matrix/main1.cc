#include <queue>
#include <utility>
#include <vector>
using namespace std;

// 行头堆的思路

class Solution {
    using P = pair<int, int>;

   public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();

        // 小顶堆
        auto cmp = [&](const P& a, const P& b) {
            return matrix[a.first][a.second] > matrix[b.first][b.second];
        };
        priority_queue<P, vector<P>, decltype(cmp)> q(cmp);
        for (int i = 0; i < m; i++) q.push({i, 0});

        int ans = 0;

        while (k-- && !q.empty()) {
            auto [i, j] = q.top();
            ans = matrix[i][j];
            q.pop();
            if (j + 1 < n) q.push({i, j + 1});
        }
        return ans;
    }
};
