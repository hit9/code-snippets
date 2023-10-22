#include <vector>
using namespace std;

//  direction 调整: (direction+1) mod 4
#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

static const vector<vector<int>> moves{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

class Solution {
   public:
    void dfs(vector<vector<int>>& matrix, int direction, int i, int j,
             vector<int>& ans) {
        int m = matrix.size();
        int n = matrix[0].size();

        if (ans.size() == m * n) return;  // 生成完毕

        ans.push_back(matrix[i][j]);
        matrix[i][j] = 999;  // 表示已访问过, 题目说 -100 <= matrix[i][j] <= 100

        // 目标 i 和 j
        // right, down, left, up
        // [i, j] 的 move
        auto move = moves[direction];
        int i1 = i + move[0];
        int j1 = j + move[1];

        // 如果目标超出棋盘 或者踩到已经访问过的地方
        // 则需要调整方向
        if (i1 < 0 || j1 < 0 || i1 >= m || j1 >= n || matrix[i1][j1] == 999) {
            // 更新方向和移动的步数
            direction = (direction + 1) % 4;
            move = moves[direction];
            i1 = i + move[0];
            j1 = j + move[1];
        }

        // 下一步移动
        dfs(matrix, direction, i1, j1, ans);
    }

    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        dfs(matrix, RIGHT, 0, 0, ans);
        return ans;
    }
};

int main(void) {
    Solution s;
    vector<vector<int>> matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    s.spiralOrder(matrix);
    return 0;
}
