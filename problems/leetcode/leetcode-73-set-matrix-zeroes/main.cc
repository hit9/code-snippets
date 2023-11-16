#include <unordered_set>
using namespace std;
class Solution {
   public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        // 找到存在零的行和列
        unordered_set<int> zeroRows;
        unordered_set<int> zeroCols;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (matrix[i][j] == 0) {
                    zeroRows.insert(i);
                    zeroCols.insert(j);
                }

        // 标 0
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (zeroRows.find(i) != zeroRows.end() ||
                    zeroCols.find(j) != zeroCols.end()) {
                    matrix[i][j] = 0;
                }
    }
};

int main(void) {
    vector<vector<int>> x{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    Solution s;
    s.setZeroes(x);
    return 0;
}
