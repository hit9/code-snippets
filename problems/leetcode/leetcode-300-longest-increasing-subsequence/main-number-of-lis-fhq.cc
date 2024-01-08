#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#define N 2001

class FHQ {
   public:
    struct {
        int l, r;   // 左右孩子
        int val;    // BST 的权值
        int rnd;    // 堆的随机值
        int size;   // 树的大小
        int len;    // 以 val 结尾的 lis 的长度
        int mxlen;  // 子树中的最大的 lis 长度
        int num;    // 以 val 结尾的 lis 的个数
        int mxnum;  // 子树中最大的 lis 的个数
    } tr[N];
    int root = 0, n = 0;  // 根节点, 最新节点的下标

    int newnode(int v, int len, int num) {
        tr[++n].val = v;
        tr[n].rnd = rand();
        tr[n].size = 1;
        tr[n].len = len;
        tr[n].mxlen = len;
        tr[n].num = num;
        tr[n].mxnum = num;
        return n;
    }

    void pushup(int p) {
        tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1;

        // 更新最大长度 和 其个数
        tr[p].mxlen = tr[p].len;
        tr[p].mxnum = tr[p].num;

        int lmaxlen = tr[p].l ? tr[tr[p].l].mxlen : 0;
        int rmaxlen = tr[p].r ? tr[tr[p].r].mxlen : 0;

        if (tr[p].mxlen < lmaxlen || tr[p].mxlen < rmaxlen) tr[p].mxnum = 0;
        if (tr[p].mxlen <= lmaxlen && rmaxlen <= lmaxlen)
            tr[p].mxnum += tr[tr[p].l].mxnum;
        if (tr[p].mxlen <= rmaxlen && lmaxlen <= rmaxlen)
            tr[p].mxnum += tr[tr[p].r].mxnum;

        tr[p].mxlen = max({lmaxlen, rmaxlen, tr[p].mxlen});
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

    void insert(int v, int len, int num) {
        int x, y;
        split(root, v, x, y);
        int z = newnode(v, len, num);
        root = merge(merge(x, z), y);
    }

    pair<int, int> ask(int v) {
        int x, y;
        split(root, v, x, y);
        int mxlen = tr[x].mxlen, mxnum = tr[x].mxnum;
        root = merge(x, y);
        return {mxlen, mxnum};
    }
};
class Solution {
   public:
    int findNumberOfLIS(vector<int> &nums) {
        FHQ treap;
        for (auto x : nums) {
            auto [mxlen, mxnum] = treap.ask(x - 1);
            treap.insert(x, mxlen + 1, max(mxnum, 1));
        }
        return treap.tr[treap.root].mxnum;
    }
};

int main(void) {
    vector<int> nums{2, 7, 4, 1, 5, 3, 4, 7, 6, 8};
    Solution s;
    cout << s.findNumberOfLIS(nums) << endl;
    return 0;
}
