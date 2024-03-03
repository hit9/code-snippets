#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
class Solution {
   public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<int> deg(n, 0);  // 入度表
        for (int x = 0; x < n; x++)
            if (edges[x] >= 0) deg[edges[x]]++;
        queue<int> q;
        for (int x = 0; x < n; x++)
            if (deg[x] == 0) q.push(x);
        vector<int> seq;  // 非环部分的拓扑序
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            seq.push_back(x);
            int y = edges[x];
            if (y >= 0 && --deg[y] == 0) q.push(y);
        }
        if (seq.size() == n) return -1;  // 无环
        // 剩余的入度非0的就是在环上的
        int ans = 0;
        vector<bool> vis(n, false);
        for (int x = 0; x < n; x++) {
            // 每个环访问一次
            if (!deg[x] || vis[x]) continue;
            vis[x] = true;
            int k = 1;
            for (int y = edges[x]; y != x; y = edges[y]) {
                k++;
                vis[y] = true;  // 设置已访问
            }
            ans = max(ans, k);
        }
        return ans;
    }
};
