#include <string>
using namespace std;
#define ch(x) (x - 'a')
class Solution {
   public:
    bool checkInclusion(string s1, string s2) {
        int d1[26], d2[26];
        memset(d1, 0, sizeof d1);
        memset(d2, 0, sizeof d2);

        for (char c : s1) d1[ch(c)]++;

        int L = 0, R = 0;
        d2[ch(s2[0])]++;

        while (R < s2.size()) {
            while (L < R && (d2[ch(s2[R])] > d1[ch(s2[R])] || !d1[ch(s2[L])])) {
                d2[ch(s2[L])]--;
                L++;
            }
            if (R - L + 1 == s1.size() && d1[ch(s2[R])]) return true;
            ++R;
            if (R < s2.size()) d2[ch(s2[R])]++;
        }
        return false;
    }
};
