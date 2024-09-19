#include <string>
#include <vector>
using namespace std;
class Solution {
   public:
    int longestContinuousSubstring(string s) {
        int n = s.size();
        vector<int> f(n, 1);
        int ans = 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] == s[i - 1] + 1) f[i] = f[i - 1] + 1;
            ans = max(ans, f[i]);
        }
        return ans;
    }
};
