#include <string>
using namespace std;

using ull = unsigned long long;
static ull mod = 10e9 + 7;

class Solution {
   public:
    int numDistinct(const string& s, const string& t) {
        int m = t.size();
        int n = s.size();

        ull dp[m + 1][n + 1];
        memset(dp, 0, sizeof dp);

        for (int j = 0; j <= n; j++)
            if (s[j] == t[0]) dp[0][j] = 1;
        for (int i = 1; i <= m; i++) {      // for i in t
            for (int j = 1; j <= n; j++) {  // for j in s
                if (i <= j) {
                    dp[i][j] = dp[i][j - 1];
                    if (t[i - 1] == s[j - 1]) {
                        dp[i][j] += dp[i - 1][j - 1] % mod;
                    }
                }
            }
        }
        return dp[m][n] % mod;
    }
};
