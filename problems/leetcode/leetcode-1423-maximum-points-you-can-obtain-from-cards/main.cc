#include <numeric>
#include <vector>
using namespace std;
class Solution {
   public:
    int maxScore(vector<int>& a, int k) {
        int n = a.size(), k1 = n - k;
        int s = accumulate(a.begin(), a.end(), 0);
        int min_sum = s, sum = 0;

        for (int L = 0, R = 0; R < n; R++) {
            sum += a[R];
            while (R - L + 1 > k1) sum -= a[L++];
            if (R - L + 1 == k1) min_sum = min(min_sum, sum);
        }
        return  s- min_sum;
    }
};
