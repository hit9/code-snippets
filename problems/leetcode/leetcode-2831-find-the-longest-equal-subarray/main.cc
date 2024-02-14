#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;
// good case: [4,4,4,3,4] k=1
// good case: [1] k=1
// good case: [2,2] k=1
class Solution {
   public:
    int longestEqualSubarray(vector<int>& a, int k) {
        unordered_map<int, int> d;
        int ans = 0;  // ans 是历史满足 之间不同元素个数不超过 k 的最高频元素的频次
        for (int L = 0, R = 0; R < a.size(); R++) {
            ans = max(ans, ++d[a[R]]);
            // 窗口的大小至少为 ans+k
            // 后续遇到更高频的, 窗口才会扩张
            while (L < R && ans + k < R - L + 1) {
                d[a[L++]]--;
            }
        }
        return ans;
    }
};
