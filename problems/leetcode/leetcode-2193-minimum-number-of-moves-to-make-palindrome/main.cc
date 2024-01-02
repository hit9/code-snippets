#include <string>
using namespace std;
class Solution {
   public:
    int minMovesToMakePalindrome(string s) {
        int n = s.size();
        int i = 0, j = n - 1;
        int ans = 0;
        while (i < j) {
            if (s[i] != s[j]) {
                int k1 = j, k2 = i;

                // 从右到左找 s[i]
                while (k1 > i && s[k1] != s[i]) k1--;
                // 从左到右找 s[j]
                while (k2 < j && s[k2] != s[j]) k2++;

                // 找不到 s[j] 或者找到的 s[i] 离右侧更近
                if (k2 == j || (j - k1) <= (k2 - i)) {
                    // 把s[k1] 换到 j 的位置
                    for (int k = k1; k < j; k++) std::swap(s[k], s[k + 1]);
                    ans += j - k1;
                } else {
                    // 把s[k2] 换到 i 的位置
                    for (int k = k2; k > i; k--) std::swap(s[k], s[k - 1]);
                    ans += k2 - i;
                }
            }
            i++, j--;
        }

        return ans;
    }
};
