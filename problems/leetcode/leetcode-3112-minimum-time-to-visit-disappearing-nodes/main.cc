#include <queue>
#include <utility>
#include <vector>
using namespace std;

using P = pair<int, int>;  // cost, x
const int inf = 0x3f3f3f3f;

class Solution {
   public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges,
                            vector<int>& disappear) {
        // 预处理边权 eds[x] => {{w, y}, ...}
        vector<vector<P>> eds(n);
        for (auto& e : edges) {
            eds[e[0]].push_back({e[2], e[1]});
            eds[e[1]].push_back({e[2], e[0]});
        }
        // 最短路答案, 初始为无穷大
        vector<int> f(n, inf);
        f[0] = 0;
        // 小根堆
        priority_queue<P, vector<P>, greater<P>> q;
        // 起始点是 0
        q.push({0, 0});
        // 访问数组
        vector<bool> vis(n, false);
        while (q.size()) {
            auto [_, x] = q.top();
            q.pop();
            if (vis[x]) continue;
            vis[x] = true;
            for (auto& [w, y] : eds[x]) {
                // 已经消失的时候, 不可再基于 y 继续扩展
                if (f[y] > f[x] + w && disappear[y] > f[x] + w) {
                    f[y] = f[x] + w;
                    q.push({f[y], y});
                }
            }
        }
        for (auto& x : f)
            if (x == inf) x = -1;
        return f;
    }
};
