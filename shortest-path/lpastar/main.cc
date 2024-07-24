// 增量计算的 A* 算法
// https://en.wikipedia.org/wiki/Lifelong_Planning_A*
// https://www.cs.cmu.edu/~maxim/files/aij04.pdf

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

const int N = 1e5 + 1;
const int inf = 0x3f3f3f3f;

// 当前是 mxm 网格寻路
const int m = 8;
// 节点总数
const int n = m * m;

// { 标号, 边权 }
using P = pair<int, int>;

// { 键值k1, 键值k2, 标号 }
using K = tuple<int, int, int>;

// 前继 {标号, 边权}
vector<vector<P>> pred;
// 后继
vector<vector<int>> succ;

// g 值: 起点到当前点的实际代价 (旧值)
// rhs 值: 起点到当前点的实际代价的临时值, 由前继节点更新而来
// 实际上都是 A* 算法中的那个实际代价 g,
// 只是分成了两种, 一个是之前的旧值 g, 一个是当前由前继传播而来的新值 rhs
// 当某部分节点更新时, 会更新其 rhs 值, 然后向后传播
// 这个传播的过程就是不断把旧值 g 更新为新的实际代价 rhs 的过程
int g[N], rhs[N];

// 优先级队列.
// 因为需要按节点标号来 "contains", "update" 之类的操作,
// 所以采用 map 而不是 priority_queue
std::map<K, int> q;

// 起始点标号, 目标点标号
int s, t;

// 启发函数, 估算当前点 x 到 目标 t 的曼哈顿距离
int h(int x) {
    // 方格内的坐标
    auto ti = t / m, tj = t % m;
    auto xi = x / m, xj = x % m;
    return abs(ti - xi) + abs(tj - xj);
}

// key 计算函数, 大体仍然是 A* 中的 (实际代价 g + 未来估价 h ) 的形式
// 是一个三元组: 第一项是 A* 中的总体代价 g + h, 第二项是说,
// 如果两个节点估计代价一样, 那么优先看实际代价小的; 第三项 是节点标号,
// 这样可以顺利支持按节点 map.find() 和 map.erase
K k(int x) { return {min(g[x], rhs[x]) + h(x), min(g[x], rhs[x]), x}; }

// 初始化
void init() {
    memset(g, 0x3f, sizeof g);
    memset(rhs, 0x3f, sizeof rhs);
    rhs[s] = 0;
    q.insert({k(s), s});
}

// 更新节点
void update(int x) {
    // 其实点不可更新, g[s] 和 rhs[s] 恒等于 0
    if (x == s) return;
    // 原始的 k
    auto k0 = k(x);
    // 根据 x 的前继节点的实际代价 g, 加上边权 w, 取最小.
    // 来获取 x 处的新代价 rhs
    rhs[x] = inf;
    for (auto& [y, w] : pred[x]) rhs[x] = min(rhs[x], g[y] + w);
    // 并把它从 q 中移除
    q.erase(k0);
    // 如果 x 的 g 和 rhs 没有对齐, 则加入队列等待更新
    if (g[x] != rhs[x]) q.insert({k(x), x});
}

// 计算最短路
void compute() {
    // q 中的节点是要把给它们的 g 和 rhs 对齐
    // 最开始, 有一部分节点通过 update 函数扰动了 rhs 值加入了队列
    // 那么要从其中实际代价最小的节点开始, 不断向后传播, 这一点和 A* 一致
    while (q.size()) {
        // 提前终止的条件:
        // 1. 队列中的最小估价已经不小于到目标的估价 (传播的已经足够远)
        // 2. 且目标处的 rhs 和 g 已经对齐 (目标处的 g 已经更新或者没有被波及到)
        // 这两点说明:
        // 1. 不可到达目标.
        // 2. 或者可以到达目标, 但是目标处已经计算完毕
        auto it = q.begin();
        if (it->first >= k(t) && rhs[t] == g[t]) break;

        // 弹出队头
        int x = it->second;
        q.erase(it);

        // 如果 rhs 更小, 说明找到了更短的一条到达 x 的路, 所以更新 g ← rhs
        // 否则, 说明上一次得到的最短路可能已经不存在, 把 g 推到无穷大,
        // 重新算一次 rhs 并把 x 重新入队.
        // 重新计算的必要性: why
        if (g[x] > rhs[x]) {
            g[x] = rhs[x];
        } else {
            g[x] = inf;
            update(x);
        }
        // 向后继节点传播, 更新邻域
        for (auto y : succ[x]) update(y);
    }
}

// 收集最短路
vector<int> collect() {
    // 从目标向前找
    vector<int> path;
    path.push_back(t);
    int x = t;
    while (x != s) {
        // 找到 g + w 最小的前继邻居
        int y1 = inf;
        int g1 = inf;
        for (const auto& [y, w] : pred[x]) {
            if (g1 > g[y] + w) {
                g1 = g[y] + w;
                y1 = y;
            }
        }
        if (y1 == inf) break;
        x = y1;
        path.push_back(x);
    }
    // 原地反转
    for (int l = 0, r = path.size() - 1; l != r; l++, r--)
        std::swap(path[l], path[r]);
    return path;
}

/////// 测试 ////////////

int GRID_MAP[m][m] = {
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

// 4方向
const P DIRECTIONS[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// 添加一个障碍物
void add_obstacle(int i, int j) {
    if (GRID_MAP[i][j]) return;
    // 会影响周围的四个邻居
    GRID_MAP[i][j] = 1;
    int x = i * m + j;
    // 到达 x 的边权全部无穷大
    for (auto& [_, w] : pred[x]) w = inf;
    // x 到达后继邻居的边权全部无穷大
    for (auto y : succ[x])
        for (auto& [x1, w] : pred[y])
            if (x1 == x) w = inf;
    // update x 和 后继邻居
    // 原则是:  update 边权有变化的边的末端节点
    update(x);
    for (auto y : succ[x]) update(y);
}

// 移除一个障碍物
void remove_obstacle(int i, int j) {
    if (!GRID_MAP[i][j]) return;
    // 会影响周围的四个邻居
    GRID_MAP[i][j] = 0;
    int x = i * m + j;
    // 到达 x 的边权全部 1
    for (auto& [_, w] : pred[x]) w = 1;
    // x 到达后继邻居的边权全部 1
    for (auto y : succ[x])
        for (auto& [x1, w] : pred[y])
            if (x1 == x) w = 1;
    // update x 和 后继邻居
    // 原则是:  update 边权有变化的边的末端节点
    update(x);
    for (auto y : succ[x]) update(y);
}

int main(void) {
    pred.resize(n);
    succ.resize(n);

    // 初始化 pred 和 succ
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int x = i * m + j;
            for (int di = 0; di < 4; di++) {
                const auto& d = DIRECTIONS[di];
                auto i1 = i + d.first, j1 = j + d.second;
                auto y = i1 * m + j1;
                if (i1 >= 0 && j1 >= 0 && i1 < m && j1 < m) {
                    // 障碍物算作无穷大的边权
                    int w = GRID_MAP[i1][j1] ? inf : 1;
                    // 后继
                    succ[x].push_back(y);
                    // 前继 {标号, 边权}
                    pred[y].push_back({x, w});
                }
            }
        }
    }

    // 设置出发点 和 目标点
    s = (m - 1) * m + 0;
    t = 0 * m + (m - 1);

    // 第一次开始计算
    init();
    compute();
    auto path = collect();
    std::cout << "shortest distance:" << g[t] << std::endl;
    for (auto x : path) std::cout << x / m << "," << x % m << std::endl;

    // 加障碍物
    add_obstacle(5, 5);
    add_obstacle(6, 5);
    compute();
    path = collect();
    std::cout << "shortest distance (updated):" << g[t] << std::endl;
    for (auto x : path) std::cout << x / m << "," << x % m << std::endl;

    // 移除碍物
    remove_obstacle(5, 5);
    remove_obstacle(6, 5);
    compute();
    path = collect();
    std::cout << "shortest distance (updated):" << g[t] << std::endl;
    for (auto x : path) std::cout << x / m << "," << x % m << std::endl;

    return 0;
}
