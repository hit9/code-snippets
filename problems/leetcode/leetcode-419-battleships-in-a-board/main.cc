#include <vector>
using namespace std;

class Solution {
   public:
    int countBattleships(vector<vector<char>>& b) {
        int m = b.size(), n = b[0].size();
        int ans1 = 0;  // 统计竖着的 (包括单个元素)
        // 自上而下的横向扫描线
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (b[i][j] == 'X' &&
                    (i == 0 || (i > 0 && b[i - 1][j] == '.'))) {
                    // 扫描到一个新的开端 X
                    if ((j > 0 && b[i][j - 1] == 'X') ||
                        (j < n - 1 && b[i][j + 1] == 'X'))  // 左右有连通的不算
                        continue;
                    ans1++;  // 新增一个
                }
            }
        }
        // 自左向右的扫描
        int ans2 = 0;  // 统计横着的,且体长 >= 2 的
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < m; i++) {
                if (b[i][j] == 'X' && b[i][j - 1] == 'X' && (j == 1 || b[i][j-2] == '.'))
                    ans2++;  // 新增一个横向的长度>=2 的
            }
        }

        return ans1 + ans2;
    }
};
