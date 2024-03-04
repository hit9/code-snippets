#include <queue>
using namespace std;
class Solution {
   public:
    bool canFinish(int n, vector<vector<int>>& p) {
        vector<vector<int>> edges(n);
        vector<int> deg(n, 0);
        for (auto e : p) {
            edges[e[0]].push_back(e[1]);
            deg[e[1]]++;  // p[1] 的入度+1
        }

        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 0) q.push(i);  // 入度为 0 的作为 bfs 起点
        }

        // 不断减小入度，如果全部遍历完所有顶点，就算成功
        int cnt = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            cnt++;
            for (auto y : edges[x]) {
                if (--deg[y] == 0) q.push(y);
            }
        }
        return cnt == n;
    }
};
