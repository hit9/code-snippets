#include <algorithm>
#include <vector>
using namespace std;
class Solution {
   public:
    int minCost(vector<vector<int>>& C) {
        int f[3] = {C[0][0], C[0][1], C[0][2]};

        for (int i = 1; i < C.size(); i++) {
            int f0 = f[0], f1 = f[1], f2 = f[2];
            f[0] = min(f1, f2) + C[i][0];
            f[1] = min(f0, f2) + C[i][1];
            f[2] = min(f0, f1) + C[i][2];
        }
        return min({f[0], f[1], f[2]});
    }
};
