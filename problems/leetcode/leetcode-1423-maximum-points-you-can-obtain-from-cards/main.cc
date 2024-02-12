#include <numeric>
#include <vector>
using namespace std;
class Solution {
   public:
    int maxScore(vector<int>& a, int k) {
        int n = a.size();
        int s = accumulate(a.begin(), a.end(), 0);
        int k1 = n - k;
        int ans = 0, sum = 0;

        for (int L = 0, R = 0; R < n; R++) {
            sum += a[R];
            while (R - L + 1 > k1) sum -= a[L++];
            if (R - L + 1 == k1) ans = max(ans, s - sum);
        }
        return ans;
    }
};
