#include <queue>
#include <utility>
#include <vector>
using namespace std;

// 层序遍历
class Solution {
   public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int cnt = 0;  // 新鲜橘子的个数

        queue<pair<int, int>> q;  // bfs queue
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) cnt++;
                if (grid[i][j] == 2) q.push({i, j});
            }
        }
        if (!cnt) return 0;        // 已经没有新鲜橘子, 直接成功
        if (q.empty()) return -1;  // 没有腐烂的橘子, 无法继续

        auto push = [&](int i, int j) {
            // 加入合法的新鲜橘子, 标记到腐烂
            if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == 1) {
                cnt--;
                grid[i][j] = 2;
                q.push({i, j});
            }
        };

        int ans = 0;

        while (!q.empty()) {
            int k = q.size();  // 层序遍历

            while (k--) {
                auto [i, j] = q.front();
                q.pop();

                // 加入上下左右邻居
                push(i - 1, j);
                push(i + 1, j);
                push(i, j - 1);
                push(i, j + 1);
            }

            ans++;
        }

        if (cnt) return -1;  // 仍存在未腐烂的
        return ans - 1;
    }
};
