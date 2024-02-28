#include <string>
using namespace std;
class Solution {
   public:
    bool isSubsequence(string s, string t) {
        if (!s.size()) return true;
        int i = 0, j = 0;
        while (i < t.size() && j < s.size()) {
            if (t[i] == s[j]) {
                j++;
            }
            if (j >= s.size()) return true;
            i++;
        }
        return false;
    }
};
