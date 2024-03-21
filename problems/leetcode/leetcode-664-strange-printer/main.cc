#include <algorithm>
#include <string>
using namespace std;
const int N = 101;
class Solution {
   public:
    int strangePrinter(string s) {
        int n = s.size();
        int f[n][n];
        memset(f, 0x3f, sizeof f);
        for (int i = 0; i < n; i++) f[i][i] = 1;
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                // 先由左右两端合并而来
                for (int k = i; k < j; k++)
                    f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
                // 如果两端相等,则可以少打印一次
                // 比如   a..p q..a
                // 可以先 aaaa aaaa
                // 也就是最外侧的一些 a 可以顺便打印出来
                if (s[i] == s[j]) f[i][j]--;
            }
        }
        return f[0][n - 1];
    }
};
