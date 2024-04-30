// 以洛谷P3372 为模板题目, 线段树维护:
//  1. 区间增加
//  2. 区间求和
//  3. 分治建树
// https://www.luogu.com.cn/problem/P3372

#include <cstdio>   // printf, scanf
#include <cstring>  // memset

#define ls (x << 1)
#define rs ((x << 1) | 1)

using ll = long long;

const int N = 1e5 + 10;

// 4 倍空间
struct {
    ll val;  // 权值, 节点 x 代表的区间的和
    ll tag;  // 延迟增加的值, 因为涉及区间更新.
} tree[N << 2];

// 关于下标:
// x=1 是第一个有效节点标号
// 区间从 1 开始, 数组下标从 1 开始

// 上推更新 x 节点, 递归后序
void pushup(int x) { tree[x].val = tree[ls].val + tree[rs].val; }

// 下放延迟标记, 递归前序
void pushdown(int x, int l, int r) {
    if (!tree[x].tag) return;

    // 修改当前节点, 增加 (r-l+1) 个 tag
    tree[x].val += (r - l + 1) * tree[x].tag;

    // 下传到子节点
    if (r != l) {
        tree[ls].tag += tree[x].tag;  // 注意是累加增量
        tree[rs].tag += tree[x].tag;
    }

    // 清理标记
    tree[x].tag = 0;
}

// 区间更新
// 区间 [p, q] 内的每个数字增加 v
// [l, r] 是当前遍历的区间, x 代表节点标号
void add(int p, int q, ll v, int l, int r, int x) {
    // 找到区间 [p, q] 的节点
    if (p <= l && r <= q) {
        // 打上延迟更新的标记
        tree[x].tag += v;
        // 执行一层
        pushdown(x, l, r);
        return;
    }

    // 找到区间 [p, q] 的节点
    auto m = (l + r) / 2;

    // 向下找的时候顺便应用延迟更新
    pushdown(x, l, r);

    // 修正其子节点的数值, 这样后序的 pushup 才有效
    pushdown(ls, l, m);
    pushdown(rs, m + 1, r);

    if (p <= m) add(p, q, v, l, m, ls);     // 向左找
    if (q > m) add(p, q, v, m + 1, r, rs);  // 向右找

    // 上浮更新
    pushup(x);
}

// 区间求和
// 返回区间 [p, q] 上的和
// [l, r] 是当前遍历的区间, x 代表节点标号
ll ask(int p, int q, int l, int r, int x) {
    // 先应用可能存在的延迟更新
    pushdown(x, l, r);

    // [p, q] 正好覆盖区间 [l, r]
    if (p <= l && r <= q) return tree[x].val;

    auto m = (l + r) / 2;

    ll ans = 0;

    if (p <= m) ans += ask(p, q, l, m, ls);     // 左子树贡献
    if (q > m) ans += ask(p, q, m + 1, r, rs);  // 右子树贡献

    return ans;
}

// 分治建树
// [l, r] 是当前构建的区间, x 代表节点标号, 从 1 开始
// a 表示初始值数组
int a[N];

void build(int l, int r, int x) {
    if (l == r) {
        tree[x].val = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, ls);      // 左边递归建树
    build(m + 1, r, rs);  // 右边递归建树
    pushup(x);            // 上浮更新 val
}

int main() {
    memset(a, 0, sizeof(a));
    memset(tree, 0, sizeof(tree));

    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    build(1, n, 1);

    while (m--) {
        int op, p, q;
        scanf("%d%d%d", &op, &p, &q);
        if (op == 1) {
            ll k;
            scanf("%lld", &k);
            add(p, q, k, 1, n, 1);
        } else if (op == 2) {
            auto ans = ask(p, q, 1, n, 1);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
