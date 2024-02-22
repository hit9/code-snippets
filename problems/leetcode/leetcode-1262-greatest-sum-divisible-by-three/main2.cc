

#include <vector>

using namespace std;
class Solution {
   public:
    int maxSumDivThree(vector<int>& a) {
        int f[3] = {0, 0, 0};

        for (auto x : a) {
            int s0 = f[0] + x;
            int s1 = f[1] + x;
            int s2 = f[2] + x;

            f[s0 % 3] = max(f[s0 % 3], s0);
            f[s1 % 3] = max(f[s1 % 3], s1);
            f[s2 % 3] = max(f[s2 % 3], s2);
        }

        return f[0];
    }
};

