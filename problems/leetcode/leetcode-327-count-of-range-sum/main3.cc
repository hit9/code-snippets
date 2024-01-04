#include <vector>

using namespace std;

#define N 100001

using ll = long long;

class FHQ {
   private:
    struct {
        int l, r;  // 左右孩子
        ll val;    // BST 的权值
        int rnd;   // 堆的随机值
        int size;  // 树的大小
    } tr[N];
    int root = 0, n = 0;  // 根节点, 最新节点的下标

    int newnode(ll v) {
        tr[++n].val = v;
        tr[n].rnd = rand();
        tr[n].size = 1;
        return n;
    }

    void pushup(int p) { tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1; }

    void split(int p, ll v, int &x, int &y) {
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

   public:
    explicit FHQ() { memset(tr, 0, sizeof tr); }

    void insert(ll v) {
        int x, y;
        split(root, v, x, y);
        int z = newnode(v);
        root = merge(merge(x, z), y);
    }

    // 返回 <= v 的节点个数
    int leqthan(ll v) {
        int x, y;
        split(root, v, x, y);
        int ans = tr[x].size;
        merge(x, y);
        return ans;
    }
};

class Solution {
   public:
    int countRangeSum(vector<int> &nums, int lower, int upper) {
        int n = nums.size();

        // 先计算前缀和 nums[0..i] => sums[i]
        ll sums[n];
        sums[0] = nums[0];
        for (int i = 1; i < n; i++) sums[i] = sums[i - 1] + nums[i];

        int ans = 0;

        FHQ tr;

        for (int i = n - 1; i >= 0; i--) {
            tr.insert(sums[i]);

            ll x = (i == 0 ? 0 : sums[i - 1]);
            ll l = lower + x, r = upper + x;

            // 求 [l, r] 内的计数
            // 转化为 <=r 的个数 - <=l-1 的个数
            int c = tr.leqthan(r) - tr.leqthan(l - 1);
            ans += c;
        }
        return ans;
    }
};
