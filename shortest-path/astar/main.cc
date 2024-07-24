#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

// m x m 网格中的 A* 寻路, 带边权
// 节点标号编码规则: i*m + j

using namespace std;

const int N = 1e5 + 1;

using P = pair<int, int>;  // (代价/边权, 节点号)
vector<vector<P>> edges;   // edges[x] => {{w, y}}  边权, 邻接点

// 一个平权的 8x8 方格，从左下角走到右上角
const int m = 8;      // 行数 (列数)
const int n = m * m;  // 节点数目 m * m

int f[N];  // s 到 x 的最短路, 已有现实代价

priority_queue<P, vector<P>, greater<P>> q;  // 小根堆
bool vis[N];                                 // 访问数组
int from[N];  // 最短路的上一步来源, 默认 0x3f3f3f3f

// 计算节点 y 到目标 t 的未来预估代价, 曼哈顿距离
int future_cost(int y, int t) {
    // 目标的坐标, TODO: 优化点可以吧 gi 和 gj 提到 while 外面
    auto ti = t / m, tj = t % m;
    // y 的坐标
    auto yi = y / m, yj = y % m;
    // 对于 y 的未来代价预估, 曼哈顿距离
    return abs(ti - yi) + abs(tj - yj);
}

// 结果是 f[t], s 是起点
void astar(int s, int t) {
    memset(f, 0x3f, sizeof f);
    memset(vis, 0, sizeof vis);
    memset(from, 0x3f, sizeof from);
    f[s] = 0;
    q.push({f[s], s});
    while (!q.empty()) {
        auto [_, x] = q.top();
        q.pop();
        if (x == t) break;  // 到达目标
        if (vis[x]) continue;
        vis[x] = true;
        // 对于 x 的每个邻居 y 和 边权
        for (const auto& [w, y] : edges[x]) {
            auto g = f[x] + w;           // s 到 y 的实际代价
            auto h = future_cost(y, t);  // y 到目标的未来代价的估计
            auto cost = g + h;           // 总代价 = 实际 + 未来
            if (f[y] > g) {  // 如果当前实际代价比之前计算的更优
                f[y] = g;    // 维护 y 的实际代价
                q.push({cost, y});
                from[y] = x;  // 最短路来源
            }
        }
    }
}

const int map[m][m] = {
    // 8x8
    {0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
};
int main(void) {
    edges.resize(n);

    // 初始化边权数组
    P directions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int x = i * m + j;
            for (int di = 0; di < 4; di++) {
                const auto& d = directions[di];
                auto i1 = i + d.first, j1 = j + d.second;
                if (i1 >= 0 && j1 >= 0 && i1 < m && j1 < m && !map[i1][j1])
                    edges[x].push_back({1, i1 * m + j1});
            }
        }
    }
    // 设置出发点 s 和目标点 t
    int s = (m - 1) * m + 0, t = 0 * m + (m - 1);
    astar(s, t);
    std::cout << "shortest distance:" << f[t] << std::endl;

    // 反向找到最短路路径
    vector<int> path;
    path.push_back(t);
    int x = t;
    while (x != s) {
        x = from[x];
        path.push_back(x);
    }
    for (int i = path.size() - 1; i >= 0; --i) {
        std::cout << path[i] / m << "," << path[i] % m << std::endl;
    }
    return 0;
}
