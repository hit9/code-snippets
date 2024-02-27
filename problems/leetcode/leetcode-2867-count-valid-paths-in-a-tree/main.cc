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
        // 预处理边 (存图)
        vector<vector<int>> ed(n + 1);
        for (auto& e : edges) {
            ed[e[0]].push_back(e[1]);
            ed[e[1]].push_back(e[0]);
        }
        // f[i] 计算子树 i 以根为端点的只含合数的路径 (1个节点也行)
        vector<int> f(n + 1, 0);
        for (int i = 1; i <= n; i++)
            if (!pt[i]) f[i] = 1;

        // 后序计算 pushup
        vector<bool> visit(n + 1, false);
        function<void(int)> up = [&](int i) {
            visit[i] = true;
            for (auto j : ed[i]) {
                if (visit[j]) continue;
                up(j);
                // 以 i 为端点的合数路径
                if (!pt[i]) f[i] += f[j];
            }
        };
        up(1);

        // 前序计算
        fill(visit.begin(), visit.end(), false);  // 复用下 visit 数组
        function<void(int)> down = [&](int i) {
            visit[i] = true;
            for (auto j : ed[i]) {
                if (visit[j]) continue;
                // 来自 i 的以 j 为端点的合数路径, 注意减去自己原本的贡献
                if (!pt[j] && !pt[i]) f[j] += f[i] - f[j];
                down(j);
            }
        };

        down(1);

        // 汇总答案
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            if (!pt[i]) continue;
            // s 是 f 的和, 即以 i 为端点的合法路径
            int s = 0;
            // q 计算 f1 * f2 的和, 即路过 i 的合法路径
            ll q = 0;
            for (auto j : ed[i]) {
                q += s * f[j];
                s += f[j];
            }
            ans += s + q;
        }
        return ans;
    }
};
