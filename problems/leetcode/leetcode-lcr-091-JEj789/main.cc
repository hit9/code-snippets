#include <algorithm>
#include <vector>
using namespace std;
class Solution {
   public:
    int minCost(vector<vector<int>>& f) {
        int n = f.size();
        for (int i = 1; i < n; i++) {
            f[i][0] += min(f[i - 1][1], f[i - 1][2]);
            f[i][1] += min(f[i - 1][0], f[i - 1][2]);
            f[i][2] += min(f[i - 1][0], f[i - 1][1]);
        }
        return min({f[n - 1][0], f[n - 1][1], f[n - 1][2]});
    }
};
