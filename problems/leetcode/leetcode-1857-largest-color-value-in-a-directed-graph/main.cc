#include <algorithm>
#include <queue>
#include <string>
#include <vector>
using namespace std;
class Solution {
   public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        // 预处理边
        vector<vector<int>> ed(n);
        for (auto& e : edges) ed[e[0]].push_back(e[1]);
        // 拓扑排序
        vector<int> deg(n, 0);
        for (int x = 0; x < n; x++)
            for (auto y : ed[x]) deg[y]++;
        queue<int> q;
        vector<int> seq;
        for (int x = 0; x < n; x++)
            if (deg[x] == 0) q.push(x);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            seq.push_back(x);
            for (auto y : ed[x])
                if (--deg[y] == 0) q.push(y);
        }
        if (seq.size() != n) return -1;  // 有环

        // DP 从后向前转移
        // f[x][color] 表示从 x 节点开始的路径颜色 color 的节点个数最大值,
        vector<vector<int>> f(n, vector<int>(26, 0));
        for (int j = n - 1; j >= 0; j--) {
            auto x = seq[j];
            f[x][colors[x] - 'a'] = 1;  // 至少为自身
            for (auto y : ed[x]) {
                for (int c = 0; c < 26; c++) {
                    int fy = f[y][c];
                    if (colors[x] - 'a' == c) fy++;  // 加上 x
                    f[x][c] = max(f[x][c], fy);
                }
            }
        }

        int ans = 0;
        for (int x = 0; x < n; x++) {
            for (int c = 0; c < 26; c++) ans = max(ans, f[x][c]);
        }
        return ans;
    }
};
