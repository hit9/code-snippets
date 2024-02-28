#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>

using namespace std;

const int N = 1e6 + 5;
using ull = unsigned long long;

ull f[N];  // f[x] 表示子树 x 的深度和
int s[N];  // s[x] 表示子树 x 的大小
int n;
bool vis[N];  // 访问数组
vector<vector<int>> edges;

int solve() {
    memset(f, 0, sizeof f);
    memset(s, 0, sizeof s);
    memset(vis, 0, sizeof vis);

    for (int x = 1; x <= n; x++) s[x] = 1;

    function<void(int, int)> up = [&](int x, int d) {
        vis[x] = true;
        f[x] = d;
        for (auto y : edges[x]) {
            if (vis[y]) continue;
            up(y, d + 1);
            f[x] += f[y];
            s[x] += s[y];
        }
    };
    up(1, 0);

    memset(vis, 0, sizeof vis);
    function<void(int)> down = [&](int x) {
        vis[x] = true;
        for (auto y : edges[x]) {
            if (vis[y]) continue;
            f[y] = max(f[y], f[x] - s[y] + s[1] - s[y]);
            down(y);
        }
    };
    down(1);

    ull maxf = 0;
    int ans = 0;
    for (int x = 1; x <= n; x++) {
        if (maxf < f[x]) {
            maxf = f[x];
            ans = x;
        }
    }
    return ans;
}

int main(void) {
    scanf("%d", &n);
    edges.resize(n + 1);

    int k = n - 1;
    while (k--) {  // n-1行
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    printf("%d\n", solve());
    return 0;
}
