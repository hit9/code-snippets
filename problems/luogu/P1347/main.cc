#include <cstdio>
#include <cstring>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

const int N = 27;
vector<unordered_set<int>> edges;  // edges[x] {y} => x < y
int n;
int a[N];    // sorted topo order
int deg[N];  // 入度表

// 0 成功
// 1 矛盾
// 2 需要继续输入
int solve() {
    memset(deg, 0, sizeof deg);
    for (int x = 1; x <= n; x++)
        for (auto y : edges[x]) ++deg[y];

    // 同时满足条件矛盾与条件不足,
    // 应该优先输出矛盾,所以对于条件不足,延迟返回,先看数据有没有矛盾
    int flag = 0;  // 条件不足 flag

    // 特判,没有出度的点应该不多于1个
    int c = 0;
    for (int x = 1; x <= n; x++) {
        if (edges[x].empty())
            if (++c > 1) {
                flag = 1;
                break;
            }
    }
    queue<int> q;

    // 加入没有入度的点
    for (int x = 1; x <= n; x++)
        if (deg[x] == 0) q.push(x);

    // 但是,如果没有入度的点超过 1 个,说明需要等待继续输入
    if (q.size() > 1) flag = 1;

    // 没有入度 0 的点一定矛盾
    if (q.empty()) return 1;

    int cnt = 0;

    while (!q.empty()) {
        auto x = q.front();
        q.pop();
        a[++cnt] = x;

        int p = 0;  // 计算没有入度的点的个数

        for (auto y : edges[x]) {
            if (--deg[y] == 0) {
                if (++p > 1) flag = 1;  // 没有入度的点超过 1 个, 无法定全序
                q.push(y);
            }
        }
    }

    if (cnt != n) return 1;  // 矛盾
    if (flag) return 2;      // 条件不足
    return 0;                // 成功
}

int main(void) {
    int m;
    scanf("%d%d", &n, &m);
    edges.resize(n + 1);

    int k = 0;

    while (m--) {
        char x, y, _;
        scanf(" %c %c %c", &x, &_, &y);
        k++;
        if (x == y) {
            printf("Inconsistency found after %d relations.\n", k);
            return 0;
        }
        edges[x - 'A' + 1].insert(y - 'A' + 1);
        int ans = solve();
        if (ans == 0) {  // 成功
            printf("Sorted sequence determined after %d relations: ", k);
            for (int i = 1; i <= n; i++) putchar(a[i] + 'A' - 1);
            putchar('.');
            putchar('\n');
            return 0;
        } else if (ans == 1) {  // 矛盾
            printf("Inconsistency found after %d relations.\n", k);
            return 0;
        }
    }
    printf("Sorted sequence cannot be determined.\n");
    return 0;
}
