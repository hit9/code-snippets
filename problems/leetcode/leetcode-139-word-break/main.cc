#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
   public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();

        unordered_set<string> st;
        for (auto x : wordDict) st.insert(x);

        bool f[n + 1];  // f(i) 表示长度为 i 的 s 的子串是否可行
        memset(f, 0, sizeof f);
        f[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) { // 枚举分割点
                if (f[j] && st.find(s.substr(j, i - j)) != st.end()) {
                    f[i] = true;break;}
            }
        }
        return f[n];
    }
};
