#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    int longestStrChain(vector<string>& words) {
        unordered_map<string, int> dp;
        sort(words.begin(), words.end(), [&](const string& a, const string& b) {
            return a.size() < b.size();
        });

        int ans = 0;

        for (auto w : words) {
            dp[w] = 1;
            for (int i = 0; i < w.size(); i++) {
                auto s = w.substr(0, i) + w.substr(i + 1, w.size() - i - 1);
                if (dp.find(s) != dp.end()) dp[w] = std::max(dp[s] + 1, dp[w]);
            }
            ans = std::max(ans, dp[w]);
        }

        return ans;
    }
};
