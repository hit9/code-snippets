#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    int maxRepOpt1(string s) {
        int n = s.size();
        unordered_map<char, int> d;
        for (auto ch : s) ++d[ch];

        // 预处理
        // g[i] 表示以 s[i] 结尾的重复字符的长度
        // f[i] 表示以 s[i] 开始的重复字符的长度
        vector<int> g(n, 1), f(n, 1);
        for (int i = 1; i < n; i++)
            if (s[i] == s[i - 1]) g[i] = g[i - 1] + 1;
        for (int i = n - 2; i >= 0; i--)
            if (s[i] == s[i + 1]) f[i] = f[i + 1] + 1;

        int ans = 1;

        // 考虑每个可能的交换点 b
        // aaaaa b ccccc
        for (int i = 0; i < n; i++) {
            ans = max(ans, g[i]);  // bbbb b
            ans = max(ans, f[i]);  // b bbbb
            if (i > 0 && d[s[i - 1]] - g[i - 1] > 0)
                ans = max(ans, g[i - 1] + 1);  // aaaa b 从其他地方换过来一个 a
            if (i < n - 1 && d[s[i + 1]] - f[i + 1] > 0)
                ans = max(ans, f[i + 1] + 1);  // b aaaa 从其他地方换过来一个 a
            if (i > 0 && i < n - 1 && s[i - 1] == s[i + 1]) {
                // aaaa b aaa
                // 至少可以换 b 为最后一个 a => aaaa aaa b
                ans = max(ans, f[i + 1] + g[i - 1]);
                // 从其他地方换一个 a 过来
                if (d[s[i - 1]] - g[i - 1] - f[i + 1] > 0)
                    ans = max(ans, f[i + 1] + 1 + g[i - 1]);
            }
        }
        return ans;
    }
};
