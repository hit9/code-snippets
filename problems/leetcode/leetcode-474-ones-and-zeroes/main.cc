#include <cstring>
#include <string>
#include <vector>

const int N = 601;
const int M1 = 101;
const int M2 = 101;

using namespace std;

class Solution {
   public:
    int findMaxForm(vector<string>& strs, int m1, int m2) {
        // 预处理体积数组, 分别是 0 和 1 的
        int v1[N], v2[N];

        for (int i = 0; i < strs.size(); i++) {
            auto& s = strs[i];
            v1[i] = count(s.begin(), s.end(), '0');
            v2[i] = s.size() - v1[i];
        }

        // 01 背包
        int f[M1][M2];
        memset(f, 0xcf,sizeof f);
        f[0][0] = 0;

        for (int i = 0; i < strs.size(); i++) {
            for (int j = m1; j >= v1[i]; j--) {      // 限制 0 的个数
                for (int k = m2; k >= v2[i]; k--) {  // 限制 1 的个数
                    f[j][k] = max(f[j][k], f[j - v1[i]][k - v2[i]] + 1);
                }
            }
        }

        int ans = 0;
        for (int j = 0; j <= m1; j++)
            for (int k = 0; k <= m2; k++) ans = max(ans, f[j][k]);
        return ans;
    }
};
