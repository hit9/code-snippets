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

// 计算节点 y 到目标 goal 的未来预估代价, 曼哈顿距离
int future_cost(int y, int goal) {
    // 目标的坐标, TODO: 优化点可以吧 gi 和 gj 提到 while 外面
    auto gi = goal / m, gj = goal % m;
    // y 的坐标
    auto yi = y / m, yj = y % m;
    // 对于 y 的未来代价预估, 曼哈顿距离
    return abs(gi - yi) + abs(gj - yj);
}

// 结果是 f[goal]
void astar(int start, int goal) {
    memset(f, 0x3f, sizeof f);
    memset(vis, 0, sizeof vis);
    memset(from, 0x3f, sizeof from);

    f[start] = 0;
    q.push({f[start], start});

    while (!q.empty()) {
        auto [_, x] = q.top();
        q.pop();

        // 到达目标
        if (x == goal) break;

        if (vis[x]) continue;
        vis[x] = true;

        // 对于 x 的每个邻居 y 和 边权
        for (const auto& [w, y] : edges[x]) {
            // 计算 start 到达 y 的实际代价
            auto g = f[x] + w;
            // 对于 y 的未来代价预估, 曼哈顿距离
            auto h = future_cost(y, goal);
            // 代价作为队列的优先级
            auto cost = g + h;
            // 只有下一步比之前计算的更优才加入队列
            if (f[y] > g) {
                // 维护 y 的实际代价
                f[y] = g;
                q.push({cost, y});
                // 计算最短路来源
                from[y] = x;
            }
        }
    }
}

int main(void) {
    edges.resize(n);

    // 设置障碍物 (1,0),(1,1),(1,2),(1,3),(1,4),(2,4),(3,4),(4,4)
    unordered_set<int> obstacles = {1 * m + 0, 1 * m + 1, 1 * m + 2, 1 * m + 3,
                                    1 * m + 4, 2 * m + 4, 3 * m + 4, 4 * m + 4};
    // 添加边，x => y
    auto add_edge = [&](int x, int y) {
        // 不可到达障碍物, 也不可从障碍物出发
        if (obstacles.find(x) == obstacles.end() &&
            obstacles.find(y) == obstacles.end())
            edges[x].push_back({1, y});
    };
    // 初始化边权数组
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int x = i * m + j;
            // 上下左右
            if (i > 0) add_edge(x, (i - 1) * m + j);
            if (j > 0) add_edge(x, i * m + (j - 1));
            if (i < m - 1) add_edge(x, (i + 1) * m + j);
            if (j < m - 1) add_edge(x, i * m + (j + 1));
        }
    }
    // 设置出发点和目标点
    int start = (m - 1) * m + 0, goal = 0 * m + (m - 1);
    astar(start, goal);
    std::cout << "shortest distance:" << f[goal] << std::endl;

    // 反向找到最短路路径
    vector<int> path;
    path.push_back(goal);
    int x = goal;
    while (x != start) {
        x = from[x];
        path.push_back(x);
    }
    for (int i = path.size() - 1; i >= 0; --i) {
        std::cout << path[i] / m << "," << path[i] % m << std::endl;
    }
    return 0;
}
