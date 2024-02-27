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
        for (int i = 2; i * i <= n; i++) {
            if (!pt[i]) continue;
            for (int j = i * i; j <= n; j += i) pt[j] = false;
        }
        // 预处理边
        vector<vector<int>> ed(n + 1);
        for (auto& e : edges) {
            ed[e[0]].push_back(e[1]);
            ed[e[1]].push_back(e[0]);
        }
        // f[i] 计算子树 i 以根为端点的只含合数的路径 (1个节点也行)
        // g[i] 计算以素数 i 为端点的合法路径数量 (至少2个节点)
        vector<int> f(n + 1, 0), g(n + 1, 0);
        for (int i = 1; i <= n; i++)
            if (!pt[i]) f[i] = 1;

        // 以 1 为根, 先计算在素数节点子树内的路径 (后序计算 pushup)
        vector<bool> visit(n + 1, false);
        function<void(int)> up = [&](int i) {
            visit[i] = true;
            for (auto j : ed[i]) {
                if (visit[j]) continue;
                up(j);
                if (pt[i]) {       // i 是素数
                    g[i] += f[j];  // 来自 j 的以 i 为端点的合法路径
                } else {
                    f[i] += f[j];  // 以 i 为端点的合数路径
                }
            }
        };
        up(1);

        // 前序计算, 不在以素数i为根的子树内的合法路径
        fill(visit.begin(), visit.end(), false);
        function<void(int)> down = [&](int i) {
            visit[i] = true;
            for (auto j : ed[i]) {
                if (visit[j]) continue;
                if (pt[j]) {
                    g[j] += f[i];  // 来自 i 以 j 为下端点的路径数
                } else {
                    // 来自 i 的以 j 为端点的合数路径
                    // 注意减去自己的贡献
                    if (!pt[i]) f[j] += f[i] - f[j];
                }
                down(j);
            }
        };

        down(1);

        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            if (!pt[i]) continue;
            ans += g[i];  // 以 i 为端点的路径
            // 另需考虑路过 i 的路径数
            for (auto j : ed[i]) {
                if (!f[j]) continue;
                for (auto k : ed[i]) {
                    if (k == j) break;
                    ans += (ll)f[k] * f[j];
                }
            }
        }
        return ans;
    }
};
