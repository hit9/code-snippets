// https://leetcode.cn/problems/number-of-islands/description/
// 200. 岛屿数量
// DFS 做法
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    // dfs 用来递归深度优先寻路，可以到达的地方全部标记 visited
    void dfs(vector<vector<char>>& g, int i, int j) {
        if (i < 0 || j < 0) return;
        if (i >= g.size() || j >= g[0].size()) return;
        if (g[i][j] == '0') return;  // 不要重复走
        g[i][j] = '0';               // 标记已经走过
        dfs(g, i - 1, j);            // 上
        dfs(g, i, j - 1);            // 左
        dfs(g, i + 1, j);            // 下
        dfs(g, i, j + 1);            // 右
    }

    int numIslands(vector<vector<char>>& g) {
        int k = 0;
        for (int i = 0; i < g.size(); i++) {
            for (int j = 0; j < g[i].size(); j++) {
                if (g[i][j] == '1') {
                    k++;
                    dfs(g, i, j);
                }
            }
        }
        return k;
    }
};

int main(void) {
    Solution solution;
    vector<vector<char>> g{{'1', '1', '1', '1', '1', '0', '1', '1', '1', '1'},
                           {'1', '0', '1', '0', '1', '1', '1', '1', '1', '1'},
                           {'0', '1', '1', '1', '0', '1', '1', '1', '1', '1'},
                           {'1', '1', '0', '1', '1', '0', '0', '0', '0', '1'},
                           {'1', '0', '1', '0', '1', '0', '0', '1', '0', '1'},
                           {'1', '0', '0', '1', '1', '1', '0', '1', '0', '0'},
                           {'0', '0', '1', '0', '0', '1', '1', '1', '1', '0'},
                           {'1', '0', '1', '1', '1', '0', '0', '1', '1', '1'},
                           {'1', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
                           {'1', '0', '1', '1', '1', '1', '1', '1', '1', '0'}};
    cout << solution.numIslands(g) << endl;
    return 0;
}
