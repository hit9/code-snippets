#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;
class Solution {
   public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> f(n, 1);
        // 来自左边的连续上升
        for (int i = 1; i < n; i++)
            if (ratings[i] > ratings[i - 1]) f[i] = f[i - 1] + 1;
        // 来自右边的连续上升
        for (int j = n - 2; j >= 0; j--) {
            if (ratings[j] > ratings[j + 1]) f[j] = max(f[j], f[j + 1] + 1);
        }
        return accumulate(f.begin(), f.end(), 0);
    }
};
