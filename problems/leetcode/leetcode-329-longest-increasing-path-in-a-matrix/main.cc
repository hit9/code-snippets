#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

// 思路:
// 因为是递增路径,所以不会出现矛盾,因此可以形成 DAG
// 建图 DAG,  求拓扑序, 然后自后向前 dp

class Solution {
   public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int tot = -1;  // 收集节点标号,从0开始
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> g(m, vector<int>(n, 0));  // g[i][j] -> tot
        int N = m * n;
        vector<vector<int>> edges(N);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = ++tot;
                int v = matrix[i][j];
                if (i > 0) {  // 上边
                    int up = matrix[i - 1][j];
                    int x = g[i - 1][j];
                    if (up < v)
                        edges[x].push_back(tot);
                    else if (v < up)
                        edges[tot].push_back(x);
                }
                if (j > 0) {  // 左边
                    int left = matrix[i][j - 1];
                    int x = g[i][j - 1];
                    if (left < v)
                        edges[x].push_back(tot);
                    else if (v < left)
                        edges[tot].push_back(x);
                }
            }
        }

        // 入度表
        vector<int> deg(N, 0);
        for (int x = 0; x < N; x++)
            for (auto y : edges[x]) deg[y]++;
        // 拓扑排序
        queue<int> q;
        vector<int> seq;  // 排序后的结果
        for (int x = 0; x < N; x++)
            if (deg[x] == 0) q.push(x);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            seq.push_back(x);
            for (auto y : edges[x])
                if (--deg[y] == 0) q.push(y);
        }

        // 从后向前 DP 转移
        // f(x) 表示 x 开始(包括x) 的最长递增路径的长度, 最开始都为 1
        vector<int> f(N, 1);
        for (int j = N - 1; j >= 0; j--) {
            auto x = seq[j];
            for (auto y : edges[x]) {
                f[x] = max(f[x], f[y] + 1);
            }
        }

        // 答案是最终最大的那个 f
        return *max_element(f.begin(), f.end());
    }
};
