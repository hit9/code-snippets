#include <bitset>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    // 行和列是否存在皇后
    bitset<9> L, C;
    bitset<18> S1, S2;  // 斜线, 左上到右下方向 ; 右上到左下方向
    vector<string> board;
    vector<vector<string>> ans;  // 答案收集
    // 去重

    // 获取 S1 斜线的下标
    inline int es1(int i, int j, int n) {
        if (i >= j) return i - j;  // [0,n)
        return n + j - i;          // [n,2n)
    }

    // 获取 S2 斜线的下标
    inline int es2(int i, int j, int n) { return es1(i, n - 1 - j, n); }

    void dfs(int n, int k, int i) {
        if (!k) {
            ans.push_back(board);  // 拷贝
            return;
        }

        if (L[i]) return;
        L[i] = 1;
        for (int j = 0; j < n; j++) {
            if (board[i][j] != '.') continue;
            if (C[j]) continue;

            int x1 = es1(i, j, n), x2 = es2(i, j, n);
            if (S1[x1]) continue;
            if (S2[x2]) continue;

            board[i][j] = 'Q';
            C[j] = 1;
            S1[x1] = 1;
            S2[x2] = 1;

            dfs(n, k - 1, i + 1);  // 直接搜索下一行

            C[j] = 0;
            S1[x1] = 0;
            S2[x2] = 0;
            board[i][j] = '.';  // 回溯
        }
        L[i] = 0;
    }
    vector<vector<string>> solveNQueens(int n) {
        board.resize(n);
        // 制作板子
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) board[i].push_back('.');
        // 跑 n 皇后
        dfs(n, n, 0);
        return ans;
    }
};
