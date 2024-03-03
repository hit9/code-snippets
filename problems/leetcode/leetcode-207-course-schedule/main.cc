#include <queue>
using namespace std;
class Solution {
   public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> edges(numCourses);
        vector<int> deg(numCourses, 0);
        for (auto p : prerequisites) {
            edges[p[0]].push_back(p[1]);
            deg[p[1]]++;  // p[1] 的入度+1
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
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
        return cnt == numCourses;
    }
};
