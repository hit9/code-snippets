#include <cstring>
#include <string>

using namespace std;

class Solution {
   public:
    string convert(string s, int m) {
        char g[1001][1001];
        memset(g, 0, sizeof g);

        int i = 0, j = 0;
        int d = 0;  // 方向: 0 down, 1 up
        for (auto x : s) {
            if (d == 0) {  // 向下走
                g[i++][j] = x;
                if (i == m) {  // 到达底部
                    d = 1;
                    i = max(0, m - 2);
                    j++;
                }
            } else if (d == 1) {  // 向上走
                g[i--][j++] = x;
                if (i == -1) {  // 到达顶部
                    d = 0;
                    i = (m == 1) ? 0 : 1;
                }
            }
        }

        int last_j = j;
        string ans;

        for (int i = 0, k = 0; k < s.size() && i < m; i++) {
            for (int j = 0; j <= last_j && k < s.size(); j++) {
                if (g[i][j]) ans += g[i][j];
            }
        }

        return ans;
    }
};
