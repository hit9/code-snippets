#include <vector>
using namespace std;

// 二次扫描

using ll = long long;
class Solution {
   public:
    long long countPaths(int n, vector<vector<int>>& edges) {
        // 预处理素数表 埃氏筛
        vector<bool> pt(n + 1, true);
        pt[0] = pt[1] = false;
        for (int x = 2; x * x <= n; x++) {
            if (!pt[x]) continue;
            for (int y = x * x; y <= n; y += x) pt[y] = false;
        }
        // 预处理边 (存图)
        vector<vector<int>> ed(n + 1);
        for (auto& e : edges) {
            ed[e[0]].push_back(e[1]);
            ed[e[1]].push_back(e[0]);
        }
        // f[x] 计算子树 x 以根为端点的只含合数的路径 (1个节点也行)
        vector<int> f(n + 1, 0);
        for (int x = 1; x <= n; x++)
            if (!pt[x]) f[x] = 1;

        // 后序计算 pushup
        vector<bool> visit(n + 1, false);
        function<void(int)> up = [&](int x) {
            visit[x] = true;
            for (auto y : ed[x]) {
                if (visit[y]) continue;
                up(y);
                // 以 x 为端点的合数路径
                if (!pt[x]) f[x] += f[y];
            }
        };
        up(1);

        // 前序计算
        fill(visit.begin(), visit.end(), false);  // 复用下 visit 数组
        function<void(int)> down = [&](int x) {
            visit[x] = true;
            for (auto y : ed[x]) {
                if (visit[y]) continue;
                // 来自 x 的以 y 为端点的合数路径, 注意减去自己原本的贡献
                if (!pt[y] && !pt[x]) f[y] += f[x] - f[y];
                down(y);
            }
        };

        down(1);

        // 汇总答案
        ll ans = 0;
        for (int x = 1; x <= n; x++) {
            if (!pt[x]) continue;
            // s 是 f 的和, 即以 x 为端点的合法路径
            int s = 0;
            // q 计算 f1 * f2 的和, 即路过 x 的合法路径
            ll q = 0;
            for (auto y : ed[x]) {
                q += s * f[y];
                s += f[y];
            }
            ans += s + q;
        }
        return ans;
    }
};
