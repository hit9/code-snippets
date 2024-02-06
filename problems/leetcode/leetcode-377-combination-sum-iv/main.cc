#include <vector>
using namespace std;

const int N = 201;
const int M = 1001;

unsigned int f[M];

class Solution {
   public:
    int combinationSum4(vector<int>& a, int target) {
        memset(f, 0, sizeof f);
        f[0] = 1;
        for (int j = 0; j <= target; j++)
            for (int i = 0; i < a.size(); i++)
                if (j >= a[i]) f[j] += f[j - a[i]];
        return f[target];
    }
};
