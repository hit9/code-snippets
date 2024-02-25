#include <string>
using namespace std;

class Solution {
   public:
    int minFlipsMonoIncr(string s) {
        int f[2];  // f[0] 表示不翻 s[i], f[1] 表示翻 s[i] 的最少次数
        f[0] = 0;
        f[1] = 1;

        for (int i = 1; i < s.size(); i++) {
            int f0 = f[0], f1 = f[1];
            if (s[i - 1] == '0' && s[i] == '0') {  // 00
                f[0] = f0;
                f[1] = min(f0, f1) + 1;
            } else if (s[i - 1] == '1' && s[i] == '0') {  // 10
                f[0] = f1;
                f[1] = min(f0, f1) + 1;
            } else if (s[i - 1] == '0' && s[i] == '1') {  // 01
                f[0] = min(f0, f1);
                f[1] = f0 + 1;
            } else {  // 11
                f[0] = min(f0, f1);
                f[1] = f1 + 1;
            }
        }

        return min(f[0], f[1]);
    }
};
