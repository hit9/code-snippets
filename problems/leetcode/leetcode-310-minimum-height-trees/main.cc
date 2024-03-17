#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
using namespace std;
class Solution {
   public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // 预处理边, 因为是无向，所以建两个
        vector<vector<int>> ed(n);
        for (auto& e : edges) {
            ed[e[0]].push_back(e[1]);
            ed[e[1]].push_back(e[0]);
        }

        // f(x) 表示以 0 为根的时候的子树 x 的高
        vector<int> f(n, 0);
        vector<bool> vis(n, false);

        // 假定一个根，先处理一次, 后序树形 dp
        function<void(int)> up = [&](int x) {
            vis[x] = true;
            for (auto y : ed[x]) {
                if (vis[y]) continue;
                up(y);  // 先处理子树 y
                f[x] = max(f[x], f[y] + 1);
            }
        };

        up(0);

        // 这一次 f[x] 表示以 x 为根的时候的树高
        // 仍从刚才的根 0 出发，前序修正 f
        fill(vis.begin(), vis.end(), false);

        // 计算以 x 为根的情况下的最高子树高度、和 次高子树高度
        // 包括 深度在内 (也就是 0 号节点方向) 一起考虑
        // 最高的子树高度
        function<pair<int, int>(int, int)> calc =
            [&](int x, int depth) -> pair<int, int> {
            int f1 = f[x] - 1;
            // 最高的子树个数
            int mc = 0;
            if (depth - 1 == f1) mc++;  // 来自 0 号节点上游
            for (auto y : ed[x]) {
                if (vis[y]) continue;  // 确保来自下游没访问过的子节点
                if (f[y] == f1) mc++;
            }

            // 次高子树高度，如果有多个最高，次高也是最高,
            // 如果没有>1个子树，则是 -2
            int f2 = -2;
            if (mc > 1)
                f2 = f1;  // 不止一个最高子树
            else if (mc == 1) {
                for (auto y : ed[x]) {
                    if (vis[y]) continue;
                    if (f[y] == f1) continue;  // 跳过最高
                    f2 = max(f2, f[y]);
                }
                // 跳过最高
                if (f1 != depth - 1) f2 = max(f2, depth);
            }
            return {f1, f2};
        };

        function<void(int, int)> down = [&](int x, int depth) {
            vis[x] = true;

            auto [f1, f2] = calc(x, depth);

            for (auto y : ed[x]) {
                if (vis[y]) continue;
                // y 不是最高的子树
                // 也就是说 x 中存在另一个子树 z 比 y 高, 再算上边 (x,y) 肯定比
                // y 更高
                if (f[y] < f1)
                    f[y] = f[x] + 1;
                else if (f[y] == f1) {
                    // y 已经是 x 的一个最高的子树
                    // 进一步看次高的另一个子树 z, 看看是否可以算上 (x,z) 和
                    // (x,y) 两个边后超过 y 的高度
                    f[y] = max(f[y], f2 + 2);
                }
                down(y, depth + 1);
            }
        };

        down(0, 0);

        // 答案收集
        vector<int> ans;
        auto min_h = *min_element(f.begin(), f.end());
        for (int x = 0; x < n; x++)
            if (min_h == f[x]) ans.push_back(x);
        return ans;
    }
};
