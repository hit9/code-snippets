// https://leetcode.cn/problems/range-sum-query-mutable
// 307. 区域和检索 - 数组可修改
// 线段树模板题

#include <vector>
using namespace std;

#define lson j << 1
#define rson (j << 1) | 1

class NumArray {
   private:
    int n;
    vector<int>& nums;
    vector<int> tree;
    int cur;

    void pushup(int j) { tree[j] = tree[lson] + tree[rson]; }

    void _build(int l, int r, int j) {
        if (l == r) {
            tree[j] = nums[cur++];
            return;
        }
        auto m = (l + r) / 2;
        _build(l, m, lson);
        _build(m + 1, r, rson);
        pushup(j);
    }

    void _update(int p, int l, int r, int val, int j) {
        if (l == r) {
            tree[j] = val;
            return;
        }
        auto m = (l + r) / 2;
        if (p <= m)
            _update(p, l, m, val, lson);
        else
            _update(p, m + 1, r, val, rson);
        pushup(j);  // 上浮更新
    }

    int _query(int ql, int qr, int l, int r, int j) {
        if (ql <= l && r <= qr) return tree[j];
        auto m = (l + r) / 2;
        int ans = 0;
        if (ql <= m) ans += _query(ql, qr, l, m, lson);
        if (qr > m) ans += _query(ql, qr, m + 1, r, rson);
        return ans;
    }

   public:
    NumArray(vector<int>& nums)
        : n(nums.size()), nums(nums), tree(vector<int>(4 * n, 0)), cur(0) {
        _build(1, n, 1);
    }

    void update(int index, int val) { _update(index + 1, 1, n, val, 1); }

    int sumRange(int left, int right) {
        return _query(left + 1, right + 1, 1, n, 1);
    }
};
