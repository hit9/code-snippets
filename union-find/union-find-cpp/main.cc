// 并查集

#include <iostream>
#include <vector>

class UnionFind {
    // 父节点数组 pa[i] 表示 i 的父节点索引
    std::vector<int> pa;
    // 大小数组 sizes[i] 表示以 i 作为父节点的元素个数
    std::vector<int> sizes;
    // 连通分量数量，即互不相连的孤岛数量
    int c;

   public:
    explicit UnionFind(int n)
        : pa(std::vector<int>(n)), sizes(std::vector<int>(n, 1)), c(n) {
        // 初始化: 自己作为父节点
        for (int i = 0; i < n; i++) pa[i] = i;
    }

    // 查找一个节点的根节点
    int Find(int x) {
        // 父节点就是自身，已经达到根节点，直接返回
        if (pa[x] == x) return x;
        // 否则继续向上递归父节点 => Find(parent)
        // 路径压缩:
        // 找到以后，直接把当前的父节点更新为更上层的父节点
        // 让树更扁平，加速后续查找
        pa[x] = Find(pa[x]);
        return pa[x];
    }

    // 合并两个节点所在的树
    void Union(int a, int b) {
        // 思路: 把一方的根节点的父节点 设置为 另一方的根节点
        // roota = Find(a)
        // rootb = Find(b)
        // pa[a] = b
        // 但是为了防止合并后的树不平衡，所以优化点: 选择把更小的树放入更大的树
        a = Find(a), b = Find(b);
        // 无需合并，已经在一根树上
        if (a == b) return;
        if (sizes[a] > sizes[b]) {
            // 把 b 并入 a
            pa[b] = a;
            sizes[a] += sizes[b];
        } else {
            pa[a] = b;
            sizes[b] += sizes[a];
        }
        // 连通后，孤岛数量减一
        c--;
    }

    // 获取以 x 为根节点的元素数量
    int Size(int x) { return sizes[x]; }

    // 返回两个节点是否连通?
    bool IsConnected(int a, int b) { return Find(a) == Find(b); }

    // 返回连通分量数量
    int ComponentsCount() { return c; }
};

int main(void) {
    UnionFind uf(5);
    uf.Union(0, 1);
    uf.Union(3, 4);
    uf.Union(1, 5);
    uf.Union(2, 4);
    std::cout << uf.Find(2) << std::endl;
    std::cout << uf.Find(5) << std::endl;
    std::cout << uf.Find(1) << std::endl;
    std::cout << uf.Find(0) << std::endl;
    std::cout << uf.Find(4) << std::endl;
    std::cout << uf.Find(3) << std::endl;

    std::cout << uf.ComponentsCount() << std::endl;

    return 0;
}
