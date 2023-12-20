#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

#define inf 0x3f3f3f3f

class Solution {
   public:
    int makeArrayIncreasing(vector<int>& a, vector<int>& b) {
        int n = a.size();

        int f[n + 1][n + 1];
        memset(f, 0x3f, sizeof f);
        f[0][0] = -1;  // 初始值最小

        sort(b.begin(), b.end());

        for (int i = 1; i <= n; i++) {
            for (int k = 0; k <= i; k++) {
                // 不动时
                if (f[i - 1][k] < a[i - 1]) f[i][k] = min(f[i][k], a[i - 1]);

                // 增加一次操作
                if (k >= 1 && f[i - 1][k - 1] != inf) {
                    auto t = upper_bound(b.begin(), b.end(), f[i - 1][k - 1]);
                    if (t != b.end()) f[i][k] = min(f[i][k], *t);
                }
            }
        }
        for (int k = 0; k <= n; k++)
            if (f[n][k] != inf) return k;
        return -1;
    }
};

int main(void) {
    vector<int> a{1, 5, 3, 6, 7};
    vector<int> b{1, 3, 2, 4};
    Solution s;
    cout << s.makeArrayIncreasing(a, b) << endl;
    return 0;
}
