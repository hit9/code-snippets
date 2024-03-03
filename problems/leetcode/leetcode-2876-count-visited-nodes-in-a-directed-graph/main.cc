#include <queue>
#include <vector>
using namespace std;

// 思路:
// 因为每个点只有一个出度,但是总共有n个边,所以必然每个连通块有一个环(你可以反证来说明这一点)
// 那么,先拓扑排序,剩余的入度没有到0的就是环上的点, 依次求每个环的大小
// 环上的答案就是环的大小,直接更新其答案
// 然后从拓扑序反向更新其他的链上节点的答案即可

class Solution {
   public:
    vector<int> countVisitedNodes(vector<int>& edges) {
        int n = edges.size();
        // 拓扑序
        vector<int> deg(n, 0);  // 入度表
        for (int x = 0; x < n; x++) deg[edges[x]]++;

        queue<int> q;
        for (int x = 0; x < n; x++)
            if (deg[x] == 0) q.push(x);

        vector<int> seq;  // 链上的拓扑序
        while (!q.empty()) {
            auto x = q.front();
            q.pop();
            seq.push_back(x);
            auto y = edges[x];
            if (--deg[y] == 0) q.push(y);
        }

        vector<int> f(n, 0);

        // 先更新环上的答案
        for (int x = 0; x < n; x++) {
            // 拓扑后环上的点的入度一定非 0
            // 每个环只会遍历 2 次 (f[x] 避免重复访问了)
            if (!deg[x] || f[x]) continue;
            int k = 1;
            // 找环的大小
            for (int y = edges[x]; y != x; y = edges[y]) k++;
            for (int y = x, j = 0; j < k; y = edges[y], j++) f[y] = k;
        }

        // 反向拓扑序, 更新链上答案
        for (int j = seq.size() - 1; j >= 0; j--) {
            auto x = seq[j], y = edges[x];
            f[x] = 1 + f[y];  // x 可以到达 y 和 自身
        }

        return f;
    }
};
