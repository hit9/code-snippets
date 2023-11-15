// 2407. 最长递增子序列 II
// https://leetcode.cn/problems/longest-increasing-subsequence-ii
// 给你一个整数数组 nums 和一个整数 k 。
// 找到 nums 中满足以下要求的最长子序列：
//
//     子序列 严格递增
//     子序列中相邻元素的差值 不超过 k 。
//
// 请你返回满足上述要求的 最长子序列 的长度。
//
// 子序列 是从一个数组中删除部分元素后，剩余元素不改变顺序得到的数组。

#include <algorithm>
#include <vector>
using namespace std;

// 线段树
// 每个节点存储一个区间上的序列长度的最值

#define ls j << 1
#define rs (j << 1) | 1

class SegTree {
   private:
    int maxn;
    int N;
    vector<int> tree;

    void pushup(int j) { tree[j] = max(tree[ls], tree[rs]); }

    // p 是序列的点位，本题中就是对应的数值 num
    // val 是要更新到的新的序列长度 length
    // j 是 tree 中的节点的下标
    // l, r 是 num 的节点 j 所描述的值域空间
    void _update(int p, int l, int r, int val, int j) {
        if (l == r) {
            tree[j] = max(tree[j], val);
            return;
        }
        auto m = (l + r) / 2;
        if (p <= m)
            _update(p, l, m, val, ls);
        else
            _update(p, m + 1, r, val, rs);

        pushup(j);  // 上浮更新
    }

    // ql, qr 是要查询的区间，在本题中就是要查询的 num 的值域区间, 也就是
    // [num-k, num-1] l, r 是当前 tree j 所描述的区间 返回 [ql, qr]
    // 的区间上所描述的最值
    int _query(int ql, int qr, int l, int r, int j) {
        if (ql <= l && r <= qr) return tree[j];
        auto m = (l + r) / 2;
        // 递归查询左右子树, 取最大值
        int ans = 0;
        if (ql <= m) ans = max(_query(ql, qr, l, m, ls), ans);
        if (qr > m) ans = max(_query(ql, qr, m + 1, r, rs), ans);
        return ans;
    }

   public:
    explicit SegTree(int maxn)
        : maxn(maxn), N(4 * maxn), tree(vector<int>(N, 0)){};
    // 更新值 num 的对应的长度值 length, 1 是树的第一个有效节点的下标
    void update(int num, int length) { _update(num, 0, maxn, length, 1); };
    // 查询值在指定区间内的 长度值 的最值
    int query(int ql, int qr) { return _query(ql, qr, 0, maxn, 1); }
    // 树根的 长度值 最值.
    int top() { return tree[1]; }
};

class Solution {
   public:
    int lengthOfLIS(vector<int>& nums, int k) {
        auto maxn = *max_element(nums.begin(), nums.end());
        SegTree sg(maxn);
        for (auto num : nums) {
            // 注意右侧是 num-1 闭合，因为要严格递增
            auto length = sg.query(num - k, num - 1) + 1;
            sg.update(num, length);
        }
        return sg.top();
    }
};

int main(void) {
    Solution s;
    vector<int> nums{4, 2, 1, 4, 3, 4, 5, 8, 15};
    s.lengthOfLIS(nums, 3);
    return 0;
}
