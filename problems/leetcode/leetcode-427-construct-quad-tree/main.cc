#include <vector>
using namespace std;
// Definition for a QuadTree node.
class Node {
   public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight,
         Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
   public:
    // 前缀和 sum[i][j] 表示以 (0,0) 为左上角, (i,j) 为右上角的矩阵的前缀和
    vector<vector<int>> sum;
    int m, n;
    Node* construct(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        sum.resize(m);
        for (int i = 0; i < m; i++) sum[i].resize(n, 0);
        // 计算前缀和
        for (int i = 0; i < m; i++) {
            // s 是当前行的前缀和(临时变量)
            int s = 0;
            for (int j = 0; j < n; j++) {
                s += grid[i][j];
                sum[i][j] += s;                         // 当前行
                if (i > 0) sum[i][j] += sum[i - 1][j];  // 上方矩阵
            }
        }
        // 递归建树
        return dfs(grid, 0, 0, m - 1, n - 1);
    }
    // 递归建树 (x1,y1) 是左上角, (x2, y2) 是右下角
    Node* dfs(vector<vector<int>>& grid, int x1, int y1, int x2, int y2) {
        // 递归终止: 越界
        if (!(x1 >= 0 && x1 < m && y1 >= 0 && y1 < n)) return nullptr;
        if (!(x2 >= 0 && x2 < m && y2 >= 0 && y2 < n)) return nullptr;
        // 递归终止: 左上角 等于 右下角, 单元格, 此时一定是叶子
        if (x1 == x2 && y1 == y2) return new Node(grid[x1][y1], true);
        // 递归终止: 当前单元格都是同一个值
        //
        //     A  |  b         B = A + b
        //   -----------
        //     c  |  D         C = A + c
        //
        //  S = A + b + c + D
        //  D <= S - B - C + A;
        int A = (x1 > 0 && y1 > 0) ? sum[x1 - 1][y1 - 1] : 0;
        int B = (x1 > 0) ? sum[x1 - 1][y2] : 0;
        int C = (y1 > 0) ? sum[x2][y1 - 1] : 0;
        int D = sum[x2][y2] - B - C + A;
        //  D 是 0 表示此区域都是 0, 算作叶子
        if (D == 0) return new Node(0, true);
        // 都是1 时, D 是元素个数为 (x2-x1+1)*(y2-y1+1) 个, 算作叶子
        if (D == (x2 - x1 + 1) * (y2 - y1 + 1)) return new Node(1, true);
        // 否则继续递归
        int dx = x2 - x1, dy = y2 - y1;
        // 中心点方格 (左上方, 下图星号的方格)
        int x3 = x1 + dx / 2, y3 = y1 + dy / 2;

        //     y1    y3       y2
        //  x1 -+------+------+-
        //      |  a   |  b   |
        //  x3  |    * |      |
        //     -+------+------+-
        //      |  c   |  d   |
        //      |      |      |
        //  x2 -+------+------+-

        auto a = dfs(grid, x1, y1, x3, y3);
        auto b = dfs(grid, x1, y3 + 1, x3, y2);
        auto c = dfs(grid, x3 + 1, y1, x2, y3);
        auto d = dfs(grid, x3 + 1, y3 + 1, x2, y2);
        // 值肯定等于 1, 否则会被前面的条件拦截住的
        return new Node(1, false, a, b, c, d);
    }
};
