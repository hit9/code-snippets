// https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/
// 2316. 统计无向图中无法互相到达点对数
// 给你一个整数 n ，表示一张 无向图 中有 n 个节点，编号为 0 到 n - 1
// 。同时给你一个二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示节点 ai 和 bi
// 之间有一条 无向 边。 请你返回 无法互相到达 的不同 点对数目 。
// 输入：n = 3, edges = [[0,1],[0,2],[1,2]] 输出：0
// 解释：所有点都能互相到达，意味着没有点对无法互相到达，所以我们返回 0 。

// 并查集

#include <vector>

using namespace std;

class UnionFind {
   private:
    vector<int> pa;
    vector<int> sizes;

   public:
    explicit UnionFind(int n) : pa(vector<int>(n)), sizes(vector<int>(n, 1)) {
        for (auto i = 0; i < n; i++) pa[i] = i;
    }

    int Find(int x) {
        if (x == pa[x]) return x;
        return pa[x] = Find(pa[x]);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        if (sizes[x] < sizes[y]) {
            pa[x] = y;
            sizes[y] += sizes[x];
        } else {
            pa[y] = x;
            sizes[x] += sizes[y];
        }
    }

    int Size(int x) { return sizes[x]; }
};

class Solution {
   public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        UnionFind uf(n);
        for (auto e : edges) {
            uf.Union(e[0], e[1]);
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            // n - 每个点所在的孤岛图的点数
            // 是这个点无法到达的点的个数
            // 总体加起来，但是每个点算了两次，所以 /2 就是「对儿」的数量
            ans += n - uf.Size(uf.Find(i));
        }
        return ans / 2;
    }
};
