#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
#define N 100005

struct fhq {
    struct {
        int l, r;  // 左右孩子
        int val;   // BST 的权值
        int rnd;   // 堆的随机值
        int size;  // 树的大小
    } tr[N];
    int root = 0, n = 0;  // 根节点, 最新节点的下标

    // 创建一个新节点
    int newnode(int v) {
        tr[++n].val = v;
        tr[n].rnd = rand();
        tr[n].size = 1;
        return n;
    }

    // 更新树的大小
    void pushup(int p) { tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1; }

    // 按值 v 进行分裂, 左子树 <=v, 右子树 > v
    // x, y 是分裂后的两颗子树的根, 执行完成后 x.val <= v < y.val
    void split(int p, int v, int &x, int &y) {
        if (!p) {  // 空树
            x = y = 0;
            return;
        }
        if (tr[p].val <= v) {
            // 递归分裂 p 的右子树
            // 左子树的根 x 已确定, y 需要继续向下带
            // 同时, p 的右节点需要指向下一层指向的左子树的根 x
            x = p;
            split(tr[p].r, v, tr[p].r, y);
        } else {  // 递归分裂 p 的左子树
            y = p;
            split(tr[p].l, v, x, tr[p].l);
        }

        // 最后, 向上更新每个子树的大小
        pushup(p);
    }

    // 按堆的随机值合并两颗子树, 返回合并后的根
    // 要求 x 树所有节点的 val 要 <= y 树所有节点的 val 值
    int merge(int x, int y) {
        if (!x || !y) return x + y;  // 存在空树的情况
        if (tr[x].rnd < tr[y].rnd) {
            // 应把 x 放上面, 先递归合并 x 的右子树 r 和 y 得到新树 z
            // 因为 x 权值更小, 所以把 z 作为 x 的右孩子
            tr[x].r = merge(tr[x].r, y);
            pushup(x);
            return x;
        } else {
            tr[y].l = merge(x, tr[y].l);
            pushup(y);
            return y;
        }
    }
    explicit fhq() { memset(tr, 0, sizeof tr); }

    int size() { return tr[root].size; }

    // 插入一个值
    void insert(int v) {
        // 按 v 分裂, 找到插入点 x <=v < y
        int x, y;
        split(root, v, x, y);
        // 新建节点
        int z = newnode(v);
        // 依次合并 x, z 和 y (权值 val 也满足如此顺序)
        root = merge(merge(x, z), y);
    }

    // 删除一个值
    void del(int v) {
        int x, y, z;
        // 先找到 v 的分割点 => x <= v < z
        split(root, v, x, z);
        // 再按 v-1 分裂 x 树 => x <= v-1 < y <= v
        split(x, v - 1, x, y);
        // y 就是值等于 v 的节点, 删除它
        // 如果找不到 v, y 就是空树, 其左右孩子都是 0, 不影响
        y = merge(tr[y].l, tr[y].r);
        // 再把 x, y, z 合并起来
        root = merge(merge(x, y), z);
    }

    // 查找排名, 满足 < v 的个数+1
    int rank(int v) {
        int x, y;
        split(root, v - 1, x, y);
        int ans = tr[x].size + 1;
        root = merge(x, y);
        return ans;
    }

    // 从子树 p 找第 k 小
    int topk(int p, int k) {
        int lsz = tr[tr[p].l].size;
        if (k == lsz + 1) return tr[p].val;
        if (k <= lsz) return topk(tr[p].l, k);
        return topk(tr[p].r, k - lsz - 1);
    }

    // 前驱, 严格 <v 的值
    int get_pre(int v) {
        int x, y;
        split(root, v - 1, x, y);
        int ans = topk(x, tr[x].size);
        root = merge(x, y);
        return ans;
    }

    // 后继, 严格 > v 的值
    int get_suc(int v) {
        int x, y;
        split(root, v, x, y);
        int ans = topk(y, 1);
        root = merge(x, y);
        return ans;
    }
};

int main(void) {
    int n;
    scanf("%d", &n);
    // 初始化
    fhq t;
    // 操作
    while (n--) {
        int opt, x;
        scanf("%d%d", &opt, &x);
        int result;
        switch (opt) {
            case 1:
                t.insert(x);
                break;
            case 2:
                t.del(x);
                break;
            case 3:
                result = t.rank(x);
                printf("%d\n", result);
                break;
            case 4:
                result = t.topk(t.root, x);
                printf("%d\n", result);
                break;
            case 5:
                result = t.get_pre(x);
                printf("%d\n", result);
                break;
            case 6:
                result = t.get_suc(x);
                printf("%d\n", result);
                break;
        }
    }
    return 0;
}
