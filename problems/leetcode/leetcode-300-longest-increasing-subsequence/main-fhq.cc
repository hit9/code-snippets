#include <algorithm>
#include <vector>
using namespace std;

#define N 2501

class FHQ {
   public:
    struct {
        int l, r;   // 左右孩子
        int val;    // BST 的权值
        int rnd;    // 堆的随机值
        int size;   // 树的大小
        int len;    // 以 val 结尾的 lis 的长度
        int mxlen;  // 子树中的最大的 lis 长度
    } tr[N];
    int root = 0, n = 0;  // 根节点, 最新节点的下标

    int newnode(int v, int len) {
        tr[++n].val = v;
        tr[n].rnd = rand();
        tr[n].size = 1;
        tr[n].len = len;
        tr[n].mxlen = len;
        return n;
    }

    void pushup(int p) {
        tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1;
        tr[p].mxlen = tr[p].len;
        if (tr[p].l) tr[p].mxlen = max(tr[p].mxlen, tr[tr[p].l].mxlen);
        if (tr[p].r) tr[p].mxlen = max(tr[p].mxlen, tr[tr[p].r].mxlen);
    }

    void split(int p, int v, int &x, int &y) {
        if (!p) {
            x = y = 0;
            return;
        }
        if (tr[p].val <= v) {
            x = p;
            split(tr[p].r, v, tr[p].r, y);
        } else {
            y = p;
            split(tr[p].l, v, x, tr[p].l);
        }

        pushup(p);
    }

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (tr[x].rnd < tr[y].rnd) {
            tr[x].r = merge(tr[x].r, y);
            pushup(x);
            return x;
        } else {
            tr[y].l = merge(x, tr[y].l);
            pushup(y);
            return y;
        }
    }

    explicit FHQ() { memset(tr, 0, sizeof tr); }

    int size() { return tr[root].size; }

    void insert(int v, int len) {
        int x, y;
        split(root, v, x, y);
        int z = newnode(v, len);
        root = merge(merge(x, z), y);
    }

    // 返回 <=v 的最大 lis 长度
    int ask(int v) {
        int x, y;
        split(root, v, x, y);
        int ans = tr[x].mxlen;
        root = merge(x, y);
        return ans;
    }
};

class Solution {
   public:
    int lengthOfLIS(vector<int> &nums) {
        FHQ treap;
        for (auto x : nums) {
            int mxlen = treap.ask(x - 1);
            treap.insert(x, mxlen + 1);
        }
        return treap.tr[treap.root].mxlen;
    }
};
