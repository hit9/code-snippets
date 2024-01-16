#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 100001;
unsigned long long seed = 1;

#define ls tr[p].l
#define rs tr[p].r

struct {
    int l, r;
    int val;
    int rnd;
    int size;
    int rev;
} tr[N];

int root = 0, tt = 0;

inline int _rand() {
    seed *= 260817;
    return (int)seed;
}

int newnode(int val) {
    ++tt;
    memset(&tr[tt], 0, sizeof tr[0]);
    tr[tt].size = 1;
    tr[tt].val = val;
    tr[tt].rnd = _rand();
    return tt;
}

void pushup(int p) {
    if (!p) return;
    tr[p].size = tr[ls].size + tr[rs].size + 1;
}

void do_reverse(int p) {
    if (!tr[p].rev) return;
    // 执行翻转
    swap(ls, rs);
    // 下传标记
    tr[ls].rev ^= 1;
    tr[rs].rev ^= 1;
    // 清理当前节点标记
    tr[p].rev = 0;
}

void pushdown(int p) {
    if (!p) return;
    do_reverse(p);
    if (ls) do_reverse(ls);
    if (rs) do_reverse(rs);
}

void split(int p, int k, int &x, int &y) {
    if (!p) {
        x = y = 0;
        return;
    }
    pushdown(p);
    if (tr[ls].size < k) {
        x = p;
        k -= tr[ls].size + 1;
        split(rs, k, rs, y);
    } else {
        y = p;
        split(ls, k, x, ls);
    }
    pushup(p);
}

int merge(int x, int y) {
    if (!x || !y) {
        return x + y;
    }
    if (tr[x].rnd < tr[y].rnd) {
        pushdown(x);
        tr[x].r = merge(tr[x].r, y);
        pushup(x);
        return x;
    } else {
        pushdown(y);
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
}

void append(int val) { root = merge(root, newnode(val)); }

void reverse(int l, int r) {
    int x, y, z;
    split(root, r, x, z);
    split(x, l - 1, x, y);
    // 打标
    tr[y].rev ^= 1;
    // 先执行一层翻转, 并传播到下一层
    do_reverse(y);
    // 合并回去
    root = merge(merge(x, y), z);
}

void output(int p) {
    if (!p) return;
    pushdown(p);
    output(ls);
    printf("%d ", tr[p].val);
    output(rs);
}

int main(void) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) append(i);
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        reverse(l, r);
    }
    output(root);
    printf("\n");
    return 0;
}
