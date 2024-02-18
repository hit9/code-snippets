#include <cstdio>
using namespace std;
const int N = 1e4 + 1;
struct UF {
    int fa[N];
    int sz[N];
    UF(int n) {
        for (int i = 1; i <= n; i++) {
            sz[i] = 1;
            fa[i] = i;
        }
    }

    int Find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = Find(fa[x]);
    }

    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a == b) return;
        if (sz[a] > sz[b]) {  // merge b to a
            fa[b] = a;
            sz[a] += sz[b];
        } else {
            fa[a] = b;
            sz[b] += sz[a];
        }
    }
};

int main(void) {
    int m, n;
    scanf("%d%d", &n, &m);
    UF u(n);
    while (m--) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        switch (op) {
            case 1:
                u.Union(x, y);
                break;
            case 2:
                printf("%s\n", u.Find(x) == u.Find(y) ? "Y" : "N");
                break;
        }
    }
    return 0;
}
