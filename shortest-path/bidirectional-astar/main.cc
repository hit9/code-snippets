// 双向 A star

#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

// m x m 网格中的 A* 寻路, 带边权
// 节点标号编码规则: i*m + j

using namespace std;

const int N = 1e5 + 1;
const int inf = 0x3f3f3f3f;

using P = pair<int, int>;  // (代价/边权, 节点号)
vector<vector<P>> edges;   // edges[x] => {{w, y}}  边权, 邻接点

// 一个平权的 8x8 方格
const int m = 8;      // 行数 (列数)
const int n = m * m;  // 节点数目 m * m

// 1 是从 s 出发的正向, 2 是从 t 出发的反向

int f1[N], f2[N];
priority_queue<P, vector<P>, greater<P>> q1, q2;  // 小根堆
bool vis1[N], vis2[N];                            // 访问数组
int from1[N], from2[N];                           // 最短路的上一步来源

// 计算节点 y 到目标 t 的未来预估代价, 曼哈顿距离
// 反向和正向的时候传入的目标不一样
int future_cost(int y, int t) {
    // 目标的坐标
    auto ti = t / m, tj = t % m;
    // y 的坐标
    auto yi = y / m, yj = y % m;
    // 对于 y 的未来代价预估, 曼哈顿距离
    return abs(ti - yi) + abs(tj - yj);
}

// 扩展一次队列 q
// 每次是说向外扩展一层
// vis 是自己的访问数组, vis_other 是对方的访问数组
// t 是本次搜索的模板
// 如果出现重合, 代表可以搜索结束
// 返回相遇点, 如果没有相遇点, 返回 inf;
int extend(decltype(q1)& q, int f[N], int from[N], bool vis[N],
           bool vis_other[N], int t) {
    int k = q.size();
    while (k--) {
        auto [_, x] = q.top();
        q.pop();
        if (x == t) break;  // 到达目标
        if (vis[x]) continue;
        vis[x] = true;
        // 判断重合
        if (vis_other[x]) return x;
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
    // 本轮没有相遇
    return inf;
}

// 返回相遇点 x , 结果是 f1[x] + f2[x]
// 没有最短路的时候返回 inf
int astar(int s, int t) {
    memset(f1, 0x3f, sizeof f1);
    memset(f2, 0x3f, sizeof f2);
    memset(vis1, 0, sizeof vis1);
    memset(vis2, 0, sizeof vis2);
    memset(from1, 0x3f, sizeof from1);
    memset(from2, 0x3f, sizeof from2);
    f1[s] = 0;
    f2[t] = 0;
    q1.push({f1[s], s});
    q2.push({f2[t], t});

    // 优先扩展点更少的
    while (!q1.empty() && !q2.empty()) {
        // x 相遇点
        int x = inf;
        // 优先扩展更小的
        if (q1.size() <= q2.size()) {
            // 扩展 1
            x = extend(q1, f1, from1, vis1, vis2, t);
        } else {
            // 扩展 2
            x = extend(q2, f2, from2, vis2, vis1, s);
        }
        if (x != inf) return x;
    }
    // 找不到
    return inf;
}

////////// 测试 ////////////

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

int main(void) {
    edges.resize(n);
    // 初始化边权数组 (四方向移动)
    P directions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int x = i * m + j;
            for (int di = 0; di < 4; di++) {
                const auto& d = directions[di];
                auto i1 = i + d.first, j1 = j + d.second;
                if (i1 >= 0 && j1 >= 0 && i1 < m && j1 < m && !grids[i1][j1])
                    edges[x].push_back({1, i1 * m + j1});
            }
        }
    }
    // 设置出发点 s (左下角) 和目标点 t (右上角)
    int s = (m - 1) * m + 0, t = 0 * m + (m - 1);
    // 开始搜索
    int x = astar(s, t);
    if (x == inf) {
        std::cout << "找不到最短路" << std::endl;
        return 0;
    }
    std::cout << "相遇点: " << x / m << "," << x % m << std::endl;
    std::cout << "shortest path is: " << f1[x] + f2[x] << std::endl;
    // 最短路径, 从相遇点收集
    vector<int> path;

    // 收集 x ==> s 的路径
    path.push_back(x);
    int y1 = x;
    while (y1 != s) {
        y1 = from1[y1];
        path.push_back(y1);
    }
    // 翻转 [x..t]
    for (int l = 0, r = path.size() - 1; l < r; l++, r--)
        std::swap(path[l], path[r]);
    // 收集 x ==> t 的路径
    int y2 = x;
    while (y2 != t) {
        y2 = from2[y2];
        path.push_back(y2);
    }

    // 打印最短路
    for (auto y : path) std::cout << y / m << "," << y % m << std::endl;

    return 0;
}
