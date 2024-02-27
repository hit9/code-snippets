#include <algorithm>
#include <string>
#include <vector>
using namespace std;
class Solution {
   public:
    string largestNumber(vector<int>& nums) {
        vector<string> strs;
        for (auto x : nums) strs.push_back(to_string(x));
        auto cmp = [&](const string& a, const string& b) -> bool {
            return a + b > b + a;
        };
        sort(strs.begin(), strs.end(), cmp);
        string ans;
        for (auto y : strs) ans += y;
        // trim leader 0
        int k = 0;
        for (auto ch : ans) {
            if (ch == '0')
                k++;
            else
                break;
        }
        if (k > 1) return ans.substr(k - 1, ans.size() - k + 1);
        return ans;
    }
};
