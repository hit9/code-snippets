#include <cstring>
#include <queue>
using namespace std;
class Solution {
   public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> deps(numCourses);
        vector<int> d(numCourses, 0);
        for (auto p : prerequisites) {
            deps[p[0]].push_back(p[1]);
            d[p[1]]++;  // p[1] 的入度+1
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (d[i] == 0) q.push(i); // 入度为 0 的作为 bfs 起点
        }

        // 不断减小入度，如果全部遍历完所有顶点，就算成功
        int cnt = 0;
        while (!q.empty()) {
            int c = q.front();
            q.pop();
            cnt++;
            for (auto x : deps[c]) {
                if (--d[x] == 0) q.push(x);
            }
        }
        return cnt == numCourses;
    }
};
