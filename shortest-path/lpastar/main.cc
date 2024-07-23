// 增量计算的 A* 算法
// https://en.wikipedia.org/wiki/Lifelong_Planning_A*
// https://www.cs.cmu.edu/~maxim/files/aij04.pdf

#include <algorithm>
#include <cstring>
#include <map>
#include <tuple>
#include <utility>

using namespace std;

const int N = 1e5 + 1;

// 当前是 mxm 网格寻路
const int m = 8;
// 节点总数
const int n = m * m;

// { 标号, 边权 }
using P = pair<int, int>;

// { 键值k1, 键值k2, 标号 }
using K = tuple<int, int, int>;

// 前继, 后继 {标号, 边权}
vector<vector<P>> pred, succ;

// g 值: 起点到当前点的实际代价 (旧值)
// rhs 值: 临时值, 由前继节点更新而来
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

// 启发函数
// 在网格中, 采用曼哈顿距离
// x 是要计算的点, t 是目标
int h(int x) {
    // 方格内的坐标
    auto ti = t / m, tj = t % m;
    auto xi = x / m, xj = x % m;
    return abs(ti - xi) + abs(tj - xj);
}

// key 计算函数, 大体仍然是 A* 中的 (实际代价 g + 未来估价 h ) 的形式
// 只不过会更细节一点:
// 第一个 min(g, rhs) + h 就是 A* 中的总体代价 g + h
// 第二个 是说, 如果两个节点的代价评估一样, 那么进一步看 g 的实际代价,
// 实际代价更小的优先.
// 第三个 是节点标号, 这样可以顺利支持按节点 map.find() 和 map.remove 等才做
K k(int x) { return {min(g[x], rhs[x]) + h(x), min(g[x], rhs[x]), x}; }

// 初始化
void init() {
    memset(g, 0x3f, sizeof g);
    memset(rhs, 0x3f, sizeof rhs);
    q.insert({k(s), s});
}

// 更新节点
void update(int x) {
    if (x != s) {  // TODO 排除掉 start 为什么?
        // 原始的 k
        auto k0 = k(x);
        // 根据 x 的前继节点重新计算其 rhs
        for (auto& [y, w] : pred[x]) rhs[x] = min(rhs[x], g[y] + w);
        // 并把它从 q 中移除
        q.erase(k0);
        // 如果 x 的 g 和 rhs 没有对齐, 则加入队列等待更新
        if (g[x] != rhs[x]) q.insert({k(x), x});
    }
}

// 计算最短路
void compute() {
    // q 的含义是, 其中的节点的实际代价 g 需要重新计算
    // 最开始, 有一部分节点通过 update 函数扰动了 rhs 值加入了队列
    // 那么要从其中实际代价最小的节点开始, 不断向后传播, 这一点和 A* 一致
    while (q.size()) {
        // 当存在后继需要重新计算的点时, 增量计算可以提前终止:
        // 1. 队列中的最小估价已经不小于到目标的估价 (传播的已经足够远)
        // 2. 且目标处的 rhs 和 g 已经对齐 (目标处的 g 已经更新或者没有被波及到)
        // 这两点说明:
        // 1. 不可到达目标.
        // 2. 或者可以到达目标, 但是目标处已经计算完毕
        if (q.begin()->first >= k(t) && rhs[t] == g[t]) break;

        // 弹出队头
        int x = q.begin()->second;
        q.erase(q.begin());

        // g[x] 保存的可能是上一轮的到达 x 的最短路信息
        // 也可能是这一轮内的另一条到达 x 的路径的最短路信息
        // 如果是只考虑是上一轮的信息的话, 可以直接赋值.
        // 但是如果是本轮中的上一次的话, 这里面有一种 x 在环上的情况,
        // x 的 rhs 上一次计算时可能使用了前继的旧 g 值, 导致其 rhs 不准确
        // 但是如果在环中的话, x 肯定会被入队考察至少两次,
        // 并且第二次肯定会遇到更大的 rhs (因为不存在负边权, x 再一次经过环推到
        // x, 总边权肯定增加了的). 因此, 总结来看, 遇到小的 rhs, 直接拿来用
        // (当然此时可能还不是准确的, 但是没事如果存在环后面会被更大的 rhs
        // 来触发重新计算来纠正的). 如果遇到更大的 rhs, 可能是准确的,
        // 也有可能不是准确的, 那么干脆直接强制重新计算.
        // 最终的目的是, g 和 rhs 对齐, 在环上也不会一直无休止的入队的,
        // 只要 g 和 rhs 对齐了, 入队就终止了.
        if (g[x] > rhs[x]) {
            g[x] = rhs[x];
        } else {
            g[x] = 0x3f3f3f3f;
            update(x);
        }
        // 向后继节点传播, 更新邻域
        for (auto [_, y] : succ[x]) update(y);
    }
}

// TODO: 寻找最短路
// Start at the goal.
// Move to the predecessor n' of the current node n for which g(n' ) + d(n' , n)
// is lowest (if the lowest score is shared by multiple nodes, each is a valid
// solution and any of them can be chosen arbitrarily). Repeat the previous step
// until you have reached the start
