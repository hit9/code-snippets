#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

using P = pair<int, int>;        //  (i, j)
using T = tuple<int, int, int>;  //  (i, j, minimal_cost)
class Solution {
   public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        queue<T> q;
        q.emplace(0, 0, 0);
        P D[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};  // 4 个移动方向

        // 到达一个方格的最小代价, 用过的破壁次数
        vector<vector<int>> costs(m, vector<int>(n, 0x3f3f3f3f));
        int ans = 0;
        // 层序遍历
        while (q.size()) {
            int r = q.size();
            while (r--) {
                auto [i, j, cost] = q.front();
                q.pop();
                if (cost > k) continue;  // 破壁次数太多, 则忽略

                // 更小的破壁路径才可以重复访问一个方格
                if (costs[i][j] <= cost) continue;
                costs[i][j] = cost;

                if (i == m - 1 && j == n - 1) return ans;
                for (int t = 0; t < 4; t++) {
                    int i1 = i + D[t].first, j1 = j + D[t].second;
                    if (i1 >= 0 && j1 >= 0 && i1 < m && j1 < n) {
                        if (grid[i1][j1])
                            q.emplace(i1, j1, cost + 1);
                        else
                            q.emplace(i1, j1, cost);
                    }
                }
            }
            ans++;
        }
        return -1;
    }
};
