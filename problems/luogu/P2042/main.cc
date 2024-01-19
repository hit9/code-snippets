#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 500005;

unsigned long long seed = 1;

// 要插入的数字
const int MAX_INSERTS = 4000005;
int to_inserts[MAX_INSERTS];

#define ls tr[p].l
#define rs tr[p].r

struct {
    int l, r;  // 左右孩子
    int val;   // 节点权值
    int rnd;   // 随机值
    int size;  // 子树大小

    int rev_tag;  // 翻转延迟标记
    int cov_tag;  // 覆盖延迟标记
    int cov_val;  // 覆盖更新的值

    int sum;   // 子树的区间和
    int mpre;  // 区间最大前缀和
    int msuf;  // 区间最大后缀和
    int msum;  // 子树内最大的区间和
} tr[N];

int root = 0, tt = 0;

// 垃圾回收栈
int gc_stack[N];
int gc_top = 0;

inline int _rand() {
    seed *= 260817;
    return int(seed);
}

int newnode(int val) {
    int i = gc_top ? gc_stack[--gc_top] : ++tt;
    memset(&tr[i], 0, sizeof tr[i]);
    tr[i].rnd = _rand();
    tr[i].size = 1;
    tr[i].msum = tr[i].sum = tr[i].val = val;
    tr[i].mpre = tr[i].msuf = max(0, val);
    return i;
}

void gc(int p) {
    if (!p) return;
    gc_stack[gc_top++] = p;
    gc(ls), gc(rs);
}

void pushup(int p) {
    tr[p].size = tr[ls].size + tr[rs].size + 1;
    tr[p].sum = tr[ls].sum + tr[rs].sum + tr[p].val;

    // 父区间的前缀和要么是左子区间的, 要么是 l.sum + p + r.mpre
    tr[p].mpre = max({tr[ls].mpre, tr[ls].sum + tr[p].val + tr[rs].mpre, 0});
    // 同理
    tr[p].msuf = max({tr[rs].msuf, tr[rs].sum + tr[p].val + tr[ls].msuf, 0});

    // 路过 p 的情况
    tr[p].msum = max(tr[ls].msuf + tr[p].val + tr[rs].mpre, tr[p].val);
    // 不路过 p 的情况,取最大
    if (ls) tr[p].msum = max(tr[p].msum, tr[ls].msum);
    if (rs) tr[p].msum = max(tr[p].msum, tr[rs].msum);
}

// 执行 p 区间的覆盖
void do_cover(int p) {
    if (!tr[p].cov_tag) return;

    // 修改值
    int c = tr[p].val = tr[p].cov_val;

    // 因为采用延迟更新
    // 所以子树的和不再等于: 左右子树的和+p.val
    // 这里要同步修改掉
    int s = tr[p].sum = c * tr[p].size;
    tr[p].mpre = tr[p].msuf = max(0, s);
    tr[p].msum = max(c, s);

    // 下传标记
    tr[ls].cov_tag = 1, tr[ls].cov_val = c;
    tr[rs].cov_tag = 1, tr[rs].cov_val = c;

    // 清理当前标记
    tr[p].cov_tag = 0;
    tr[p].cov_val = 0;
}

void do_reverse(int p) {
    if (!tr[p].rev_tag) return;
    // 翻转
    swap(ls, rs);
    // 还要翻转前后缀和
    swap(tr[p].mpre, tr[p].msuf);
    // 向下标记
    tr[ls].rev_tag ^= 1;
    tr[rs].rev_tag ^= 1;
    // 清理当前标记
    tr[p].rev_tag = 0;
}

void pushdown(int p) {
    if (!p) return;

    // 区间翻转
    do_reverse(p);
    // 向下标记, 多执行一层
    if (ls) do_reverse(ls);
    if (rs) do_reverse(rs);

    // 区间覆盖
    do_cover(p);
    // 区间覆盖要多向前执行一层
    // 因为左右子树其中一个变化, 另一半也要变化
    // 这样 sum 查询才是准的
    if (ls) do_cover(ls);
    if (rs) do_cover(rs);
}

// 按位置分裂，左边的树位置 [1,k]
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
    if (!x || !y) return x + y;
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

// 追加一个新数字
void append(int val) { root = merge(root, newnode(val)); }

// 对 to_inserts 二分建树
int build(int l, int r) {
    if (l == r) return newnode(to_inserts[l]);
    int mid = (l + r) >> 1;
    return merge(build(l, mid), build(mid + 1, r));
}

// 在 k 处插入 tot 个数字
// k = 0 时在队头插入
void insert(int k, int tot) {
    int x, y;
    split(root, k, x, y);
    int z = build(1, tot);
    root = merge(merge(x, z), y);
}

// 朴素做法，TEL
void insert1(int k, int tot) {
    int x, y;
    split(root, k, x, y);
    for (int i = 1; i <= tot; i++) x = merge(x, newnode(to_inserts[i]));
    root = merge(x, y);
}

// 从第 k 个开始, 切出子树 x, y, z
void help_split(int &x, int &y, int &z, int k, int tot) {
    int l = k, r = k + tot - 1;
    split(root, r, x, z);
    split(x, l - 1, x, y);
}

// 在 k 处删除 tot 个数字
void del(int k, int tot) {
    int x, y, z;
    help_split(x, y, z, k, tot);
    gc(y);
    root = merge(x, z);
}

// 在 k 处翻转 tot 个
void reverse(int k, int tot) {
    int x, y, z;
    help_split(x, y, z, k, tot);
    // 打标
    tr[y].rev_tag ^= 1;
    // 执行一层
    do_reverse(y);
    root = merge(merge(x, y), z);
}

// 从当前数列的第 k 个数字开始的连续 tot 个数字统一修改为 c
void makesame(int k, int tot, int c) {
    int x, y, z;
    help_split(x, y, z, k, tot);
    // 打标
    tr[y].cov_tag = 1;
    tr[y].cov_val = c;
    // 执行一层
    do_cover(y);
    root = merge(merge(x, y), z);
}

// 计算从当前数列的第 k 个数字开始的 tot 个数字的和并输出
int getsum(int k, int tot) {
    int x, y, z;
    help_split(x, y, z, k, tot);
    int ans = tr[y].sum;
    root = merge(merge(x, y), z);
    return ans;
}

// 求出当前数列中和最大的一段子列，并输出最大和
int maxsum() { return tr[root].msum; }

void output(int p) {
    if (!p) return;
    pushdown(p);
    output(tr[p].l);
    printf("%d ", tr[p].val);
    output(tr[p].r);
}

int main(void) {
    int n, m;
    scanf("%d%d", &n, &m);
    // 初始化
    for (int i = 1; i <= n; i++) {
        int val;
        scanf("%d", &val);
        append(val);
    }
    // 读取操作
    char op[10];
    while (m--) {
        scanf("%9s", op);
        int k, tot, c, ans;
        switch (op[0]) {
            case 'I':  // 插入
                scanf("%d%d", &k, &tot);
                for (int i = 1; i <= tot; i++) scanf("%d", &to_inserts[i]);
                insert(k, tot);
                break;
            case 'D':  // 删除
                scanf("%d%d", &k, &tot);
                del(k, tot);
                break;
            case 'R':  // 翻转
                scanf("%d%d", &k, &tot);
                reverse(k, tot);
                break;
            case 'G':  // 区间求和
                scanf("%d%d", &k, &tot);
                ans = getsum(k, tot);
                printf("%d\n", ans);
                break;
            case 'M':
                if (op[2] == 'K') {  // 覆盖
                    scanf("%d%d%d", &k, &tot, &c);
                    makesame(k, tot, c);
                } else {  // 求最大子列和
                    ans = maxsum();
                    printf("%d\n", ans);
                }
                break;
        }
    }
    return 0;
}
