#include <cstdio>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

const int N = 500 + 1;
int n;
vector<vector<int>> edges;
queue<int> q;  // q 是拓扑队列
vector<int> deg;
unordered_set<int> rem;  // 待拓扑输出的节点列表

// flag=true 时会操作 rem 集合
bool topo(bool flag) {
    // 执行一次
    int cnt = rem.size();
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cnt--;
        if (flag) rem.erase(x);
        for (auto y : edges[x])
            if (--deg[y] == 0) q.push(y);
    }
    return cnt == 0;
}

// 返回 0 表示成功
bool solve() {
    // 初始化入度表
    deg.resize(n + 1);
    for (int x = 1; x <= n; x++)
        for (auto y : edges[x]) ++deg[y];

    // 全部加入剩余列表
    for (int x = 1; x <= n; x++) rem.insert(x);

    // 把所有入度0的入队
    for (auto x : rem)
        if (deg[x] == 0) q.push(x);

    // 先执行一次拓扑
    if (topo(true)) return true;  // 已经是 DAG

    // 找到所有入度 1 的
    auto deg1 = deg;  // copy
    for (auto x : rem) {
        if (deg[x] != 1) continue;
        // 删其一个入度, 继续执行一次拓扑
        deg[x]--;
        // 入度为 0 的入队
        q.push(x);
        if (topo(false)) return true;
        // 恢复入度
        deg = deg1;
    }

    return false;
}

int main(void) {
    int m;
    scanf("%d%d", &n, &m);
    edges.resize(n + 1);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].push_back(y);
    }

    if (solve())
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
