#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> d1;  // p 的字符统计
        unordered_map<char, int> d2;  // 窗口内的字符统计
        for (auto ch : p) d1[ch]++;
        auto check = [&]() {
            for (char ch = 'a'; ch <= 'z'; ch++)
                if (d1[ch] != d2[ch]) return false;
            return true;
        };
        int L = 0;
        vector<int> ans;
        for (int R = 0; R < s.size();R++){
            d2[s[R]]++;
            while (L < R && R - L + 1 > p.size()) d2[s[L++]]--;
            if (check()) ans.push_back(L);
        }
        return ans;
    }
};
