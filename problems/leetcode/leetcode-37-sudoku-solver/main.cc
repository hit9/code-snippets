#include <bitset>
#include <cstring>
#include <vector>
using namespace std;
class Solution {
   public:
    bitset<9> L[9];  // L[i] 的第 x 个比特表示第 i 行有数字 x+1 填入
    bitset<9> C[9];  // C[j] 的第 x 个比特表示第 j 列有数字 x+1 填入
    bitset<9> G[3][3];  // G[k] 的第 x 个比特表示在第 k 个 3x3 小方格内有数字
                        // x+1 填入, k = i/3,j/3

    bool dfs(vector<vector<char>>& board, int k) {
        if (!k) return true;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') continue;

                auto mi = i / 3, mj = j / 3;

                // 此行无剩余数字可以填入
                if (L[i].count() >= 9) return false;

                // 此列无剩余数字可以填入
                if (C[j].count() >= 9) return false;

                // 小方格内没有剩余数字可以填入
                if (G[mi][mj].count() >= 9) return false;

                // 尝试填入 x, 其中 x+1 = 1~9
                for (int x = 0; x < 9; x++) {
                    if (!L[i][x] && !C[j][x] && !G[mi][mj][x]) {
                        board[i][j] = x + '1';
                        L[i][x] = 1;
                        C[j][x] = 1;
                        G[mi][mj][x] = 1;

                        if (dfs(board, k - 1)) return true;

                        // 回溯x, 换一个数字
                        L[i][x] = 0;
                        C[j][x] = 0;
                        G[mi][mj][x] = 0;
                    }
                }

                // 此方格填入失败
                board[i][j] = '.';
                return false;
            }
        }

        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        int k = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int x = board[i][j] - '1';
                    L[i][x] = 1;
                    C[j][x] = 1;
                    G[i / 3][j / 3][x] = 1;
                } else
                    k++;  // 待解决的方格数目
            }
        }

        // 处理
        dfs(board, k);
    }
};
