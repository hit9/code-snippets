#include <string>
using namespace std;
class Solution {
   public:
    int countKeyChanges(string s) {
        int k = 'a' - 'A';
        int ans = 0;
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == s[i - 1]) continue;
            if (s[i] <= 'z' && s[i] >= 'a' && s[i] - k == s[i - 1]) continue;
            if (s[i] <= 'Z' && s[i] >= 'A' && s[i] + k == s[i - 1]) continue;
            ++ans;
        }
        return ans;
    }
};
