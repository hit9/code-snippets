#include <string>
#include <unordered_map>

using namespace std;

// 滑窗方法

class Solution {
   public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> d; // 窗口内的元素频次统计
        int c = 0;  // 窗口内的元素种数
        int ans = 0;
        for (int L = 0, R = 0; R < s.size(); R++) {
            if (++d[s[R]] == 1) c++;
            while (L < R && c < R - L +1) {
                if (--d[s[L++]] == 0) c--;
            }
            ans = max(ans, R - L + 1);
        }
        return ans;
    }
};
