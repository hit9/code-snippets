#include <bitset>
#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        // 预处理边
        vector<vector<int>> ed(n);
        for (auto& e : edges) ed[e[0]].push_back(e[1]);

        // 拓扑排序
        vector<int> seq(n);

        vector<int> deg(n, 0);  // 入度表
        for (int x = 0; x < n; x++)
            for (auto y : ed[x]) ++deg[y];

        queue<int> q;
        int cnt = 0;

        for (int x = 0; x < n; x++)
            if (deg[x] == 0) q.push(x);

        while (!q.empty()) {
            auto x = q.front();
            q.pop();
            seq[cnt++] = x;
            for (auto y : ed[x])
                if (--deg[y] == 0) q.push(y);
        }

        // V[x] 的第 y 位是 1 表示可以 x 是 y 的祖先
        vector<bitset<1000>> V(n, 0);
        for (int j = 0; j < n; j++) {
            auto x = seq[j];
            for (auto y : ed[x]) {
                V[y][x] = true;  // x 是 y 的祖先
                V[y] |= V[x];    // 并且并入 x 的祖先
            }
        }

        // 输出答案
        vector<vector<int>> ans(n);
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {  // 祖先按升序排列
                if (V[x][y]) ans[x].push_back(y);
            }
        }
        return ans;
    }
};
