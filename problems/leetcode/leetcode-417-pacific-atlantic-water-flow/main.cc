#include <cstring>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

using P = pair<int, int>;  // (i,j)
vector<P> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
   public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& a) {
        int m = a.size(), n = a[0].size();

        queue<P> q1, q2;
        for (int i = 0; i < m; i++) q1.push({i, 0});
        for (int j = 1; j < n; j++) q1.push({0, j});
        for (int i = m - 1; i >= 0; i--) q2.push({i, n - 1});
        for (int j = n - 2; j >= 0; j--) q2.push({m - 1, j});

        int vis[m][n];
        memset(vis, 0, sizeof vis);

        while (q1.size()) {
            auto [i, j] = q1.front();
            q1.pop();
            if (vis[i][j] & 1) continue;
            vis[i][j] |= 1;
            for (auto& d : directions) {
                auto i1 = i + d.first, j1 = j + d.second;
                if (i1 >= 0 && j1 >= 0 && i1 < m && j1 < n &&
                    a[i1][j1] >= a[i][j])
                    q1.push({i1, j1});
            }
        }

        while (q2.size()) {
            auto [i, j] = q2.front();
            q2.pop();
            if (vis[i][j] & 2) continue;
            vis[i][j] |= 2;
            for (auto& d : directions) {
                auto i1 = i + d.first, j1 = j + d.second;
                if (i1 >= 0 && j1 >= 0 && i1 < m && j1 < n &&
                    a[i1][j1] >= a[i][j])
                    q2.push({i1, j1});
            }
        }
        vector<vector<int>> ans;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (vis[i][j] == 3) ans.push_back({i, j});
        return ans;
    }
};
