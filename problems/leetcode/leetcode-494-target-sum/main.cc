#include <numeric>
#include <vector>
using namespace std;
class Solution {
   public:
    int findTargetSumWays(vector<int>& a, int target) {
        int sum = accumulate(a.begin(), a.end(), 0);
        int m = (sum - target);
        if (m & 1 || m < 0) return 0;
        m >>= 1; // /2
        int n = a.size();
        int f[2001];
        memset(f, 0, sizeof f);
        f[0] = 1;
        for (int i = 0; i < n; i++)
            for (int j = m; j >= a[i]; j--) f[j] += f[j - a[i]];
        return f[m];
    }
};
