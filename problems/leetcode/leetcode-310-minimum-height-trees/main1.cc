
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // 特判: 单个节点
        if (edges.empty()) return {0};

        // 预处理边, 因为是无向，所以建两个
        vector<vector<int>> ed(n);
        for (auto& e : edges) {
            ed[e[0]].push_back(e[1]);
            ed[e[1]].push_back(e[0]);
        }

        // 入度表
        vector<int> deg(n, 0);
        for (int x = 0; x < n; x++)
            for (auto y : ed[x]) ++deg[y];

        // 添加入队为 1 的点
        queue<int> q;
        for (int x = 0; x < n; x++)
            if (deg[x] == 1) q.push(x);

        // 计算层数
        int lv = 0;

        // 层序, 最后一层的是最小高度树的节点
        vector<int> ans;
        while (q.size()) {
            int k = q.size();
            ans.clear();
            while (k--) {
                auto x = q.front();
                ans.push_back(x);
                q.pop();
                for (auto y : ed[x])
                    if (--deg[y] == 1) q.push(y);
            }
            lv++;
        }

        return ans;
    }
};
