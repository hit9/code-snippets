#include <vector>
using namespace std;

const int N = 301;
const int M = 5001;
int f[M];

class Solution {
   public:
    int change(int m, vector<int>& a) {
        memset(f, 0, sizeof f);
        f[0] = 1;
        for (int i = 0; i < a.size(); i++)
            for (int j = a[i]; j <= m; j++) f[j] += f[j - a[i]];
    return f[m];
    }
};
