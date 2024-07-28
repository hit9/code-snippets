// 流场寻路 (适合大量 Agent 共同寻路到同一个目标)
// 1. 从目标点应用 Dijkstra 算法得到 dist 场
// 2. 从 dist 场计算流向 flow 场

#include <iomanip>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// 一对数字
using P = pair<int, int>;

// 存图 edges[x] => {{w, y}} 边权,邻接点
vector<vector<P>> edges;

const int m = 8;      // 测试用 mxm 的网格
const int n = m * m;  // 点的总数量
int t;                // 目标点

// 距离场, dist[x] 存储 x 到达目标 t 的最短路径
int dist[n];

// 计算 dist 的时候的访问数组
bool vis[n];

// 小根堆
priority_queue<P, vector<P>, greater<P>> q;

// 支持的距离 8 方向, 前4个是水平竖直方向,后面的是斜角方向
// 对应 Arrows.font: ABCDEGH
const pair<int, int> DIRECTIONS[8] = {
    {0, 1},    // 右
    {1, 0},    // 下
    {0, -1},   // 左
    {-1, 0},   // 上
    {1, 1},    // 右下
    {1, -1},   // 左下
    {-1, -1},  // 左上
    {-1, 1},   // 右上
};

// 方向的字符表示
const char DIRECTION_REPL[8][4] = {
    "→", "↓", "←", "↑", "↘", "↙", "↖", "↗",
};

// 要支持的方向 4 或者 8
const int MAX_DIRECTIONS = 8;

// 流场, 对应方向的下标
// 默认设置为 -1 (表示无路可走)
int flow[m][m];

// 从目标出发, 采用 dijkstra 算法计算距离场
// 建图的标号 : i*m+j => x
void calc_dist() {
    memset(dist, 0x3f, sizeof dist);
    memset(vis, 0, sizeof vis);
    dist[t] = 0;
    q.push({dist[t], t});
    while (!q.empty()) {
        auto [_, x] = q.top();
        q.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (const auto& [w, y] : edges[x]) {
            if (dist[y] > dist[x] + w) {
                dist[y] = dist[x] + w;
                q.push({dist[y], y});
            }
        }
    }
}

// 地图
const int grids[m][m] = {
    // 8x8
    // clang-format off
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    // clang-format on
};

// 从距离场计算流场, 每个方格的方向指向最短的邻居
void calc_flow() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            // 记录最小的 dist 的邻居
            int min_dist = 0x3f3f3f3f;
            // 默认情况下, 方向值是 -1
            flow[i][j] = -1;
            // 如果当前格子是障碍物, 则不考虑流向
            if (grids[i][j]) continue;
            for (int k = 0; k < MAX_DIRECTIONS; k++) {
                const auto& d = DIRECTIONS[k];
                auto i1 = i + d.first, j1 = j + d.second;
                if (i1 >= 0 && i1 < m && j1 >= 0 && j1 < m and !grids[i1][j1]) {
                    // 确保邻居方格是合法的, 且不是障碍物
                    int y = i1 * m + j1;
                    if (min_dist > dist[y]) {
                        min_dist = dist[y];
                        flow[i][j] = k;
                    }
                }
            }
        }
    }
}

// 查询最短路 (i,j)->t, 返回 false 表示失败
bool find(int i, int j, vector<P>& path) {
    P x = {i, j};
    path.push_back(x);
    // 目标
    int ti = t / m, tj = t % m;
    while (!(i == ti && j == tj)) {
        if (flow[i][j] == -1) return false;
        const auto& d = DIRECTIONS[flow[i][j]];
        i += d.first;
        j += d.second;
        x = {i, j};
        path.push_back(x);
    }
    return true;
}

void print_path_from(int i, int j) {
    vector<P> path;
    if (!find(i, j, path)) {
        std::cout << "find path failed from " << "(" << i << "," << j << ")"
                  << std::endl;
        return;
    }
    std::cout << "find path successful from " << "(" << i << "," << j
              << "): " << dist[i * m + j] << std::endl;
    for (auto [i, j] : path) {
        std::cout << "(" << i << "," << j << ")" << std::endl;
    }
}

int main(void) {
    edges.resize(n);

    // 初始化边权数组
    // 注意!!!!!!!!!!: 实际中 edges 只被用在 dijkstra 中
    // 所以要注意反向建边. 这里是方格地图, 所以才正反都可以.
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int x = i * m + j;
            for (int di = 0; di < MAX_DIRECTIONS; di++) {
                const auto& d = DIRECTIONS[di];
                auto i1 = i + d.first, j1 = j + d.second;
                if (i1 >= 0 && j1 >= 0 && i1 < m && j1 < m && !grids[i1][j1])
                    edges[x].push_back({1, i1 * m + j1});
            }
        }
    }

    // 设置目标点 (右上角)
    t = 0 * m + (m - 1);

    // 计算 dist 和 flow 场
    calc_dist();
    calc_flow();

    // 打印下距离场
    std::cout << "dist field:" << std::endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int f = dist[i * m + j];
            std::cout << std::setw(4);
            // 不可达
            if (f == 0x3f3f3f3f)
                std::cout << "-";
            else
                std::cout << f;
        }
        std::cout << std::endl;
    }

    // 打印下流场
    std::cout << "flow field:" << std::endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int k = flow[i][j];
            // 不可达
            if (k == -1)
                std::cout << std::setw(4) << "-";
            else
                std::cout << std::setw(6) << DIRECTION_REPL[k];
        }
        std::cout << std::endl;
    }

    // 构造几个出发点, 询问最短路
    print_path_from(m - 1, 0);
    print_path_from(2, 3);

    return 0;
}
