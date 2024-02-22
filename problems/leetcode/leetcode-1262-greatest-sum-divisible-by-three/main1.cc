
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSumDivThree(vector<int>& a) {
        int f[3] = {0, 0, 0};

        for (auto x : a) {
            int s[3];
            for (int j = 0; j <= 2; j++) s[j] = f[j] + x;

            for (int j = 0; j <= 2; j++) {
                int k = s[j] % 3;
                f[k] = max(f[k], s[j]);
            }
        }

        return f[0];
    }
};
