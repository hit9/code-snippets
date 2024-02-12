#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    int subarraysWithKDistinct(vector<int>& a, int k) {
        // 窗口1: <= k, 窗口2: <k
        // 两个窗口之间的个数即是答案
        unordered_map<int, int> d1, d2;
        int c1 = 0, c2 = 0, ans = 0;
        for (int L1 = 0, L2 = 0, R = 0; R < a.size(); R++) {
            if (++d1[a[R]] == 1) c1++;
            while (L1 < R && c1 > k) {
                if (--d1[a[L1++]] == 0) c1--;
            }
            if (++d2[a[R]] == 1) c2++;
            while (L2 <= R && c2 >= k) {  // 注意,允许空窗
                if (--d2[a[L2++]] == 0) c2--;
            }
            ans += L2 - L1;
        }
        return ans;
    }
};
