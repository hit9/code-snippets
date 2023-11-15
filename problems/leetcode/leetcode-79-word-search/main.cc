// https://leetcode.cn/problems/word-search/description/?envType=study-plan-v2&envId=top-100-liked
// 79 单词搜索


#include <string>
#include <vector>
using namespace std;
class Solution {
   public:
    // i, j 是当前搜索的起始位置
    // k 是当前已经成功匹配的字符个数
    // visit 标记访问标记
    bool search(vector<vector<char>>& board, string& word,
                vector<vector<bool>>& visit, int i, int j, int k) {
        if (k == word.size()) return true;

        int m = board.size();
        int n = board[0].size();

        // 跨出棋盘
        if (i < 0 || i >= m || j < 0 || j >= n) return false;

        // 已经搜索过的，不必再搜索
        if (visit[i][j]) return false;

        if (board[i][j] != word[k]) return false;

        visit[i][j] = true;

        // 上下左右搜索 || 遇到一个真会迅速 break 的
        if (search(board, word, visit, i, j + 1, k + 1)) return true;
        if (search(board, word, visit, i + 1, j, k + 1)) return true;
        if (search(board, word, visit, i, j - 1, k + 1)) return true;
        if (search(board, word, visit, i - 1, j, k + 1)) return true;

        // 回溯
        visit[i][j] = false;
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        if (m * n < word.size()) return false;

        // 访问标记数组
        vector<vector<bool>> visit(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (search(board, word, visit, i, j, 0)) return true;
            }
        }
        return false;
    }
};
