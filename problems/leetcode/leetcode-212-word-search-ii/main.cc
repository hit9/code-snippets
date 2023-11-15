// https://leetcode.cn/problems/word-search-ii/
// 212 单词搜索 ii

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    // i, j 是当前搜索的起始位置
    // k 是当前已经成功匹配的字符个数
    // visit 标记访问标记
    bool search(vector<vector<char>>& board, string& word,
                vector<vector<bool>>& visit, unordered_map<char, int>& d, int i,
                int j, int k) {
        if (k == word.size()) return true;

        int m = board.size();
        int n = board[0].size();

        // 跨出棋盘
        if (i < 0 || i >= m || j < 0 || j >= n) return false;

        // 已经搜索过的，不必再搜索
        if (visit[i][j]) return false;

        // 字典中已经没有这个字符
        if (d[word[k]] == 0) return false;

        if (board[i][j] != word[k]) return false;

        visit[i][j] = true;
        d[board[i][j]]--;

        // 上下左右搜索
        auto b = search(board, word, visit, d, i, j + 1, k + 1) ||
                 search(board, word, visit, d, i + 1, j, k + 1) ||
                 search(board, word, visit, d, i, j - 1, k + 1) ||
                 search(board, word, visit, d, i - 1, j, k + 1);

        // 回溯
        visit[i][j] = false;
        d[board[i][j]]++;
        return b;
    }
    vector<string> findWords(vector<vector<char>>& board,
                             vector<string>& words) {
        int m = board.size();
        int n = board[0].size();

        vector<string> ans;

        // 字符频次字典
        unordered_map<char, int> d;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                d[board[i][j]]++;
            }
        }

        // 访问标记数组
        vector<vector<bool>> visit(m, vector<bool>(n, false));

        for (auto& word : words) {
            if (word.size() > m * n) continue;

            // 如果尾字符有更低的频率，则反转
            string w = word;
            if (d[word[word.size() - 1]] < d[word[0]]) reverse(w);

            bool found = false;

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (search(board, w, visit, d, i, j, 0)) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) ans.push_back(word);
        }
        return ans;
    }

    void reverse(string& word) {
        for (int i = 0, j = word.size() - 1; i < j; i++, j--) {
            std::swap(word[i], word[j]);
        }
    }
};
