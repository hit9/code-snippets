// https://leetcode.cn/problems/longest-substring-with-at-most-two-distinct-characters
// 159. 至多包含两个不同字符的最长子串
// 给你一个字符串 s ，请你找出 至多 包含 两个不同字符

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
   public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        if (s.size() <= 1) return 1;

        int left = 0, right = 0;
        unordered_map<char, int> d;

        int ans = 0;

        while (right < s.size()) {
            d[s[right]]++;

            while (d.size() > 2 && left < right) {
                d[s[left]]--;
                if (d[s[left]] == 0) d.erase(s[left]);
                left++;
            }

            ans = std::max(ans, right - left + 1);

            right++;
        }

        return ans;
    }
};

int main(void) {
    Solution solution;
    cout << solution.lengthOfLongestSubstringTwoDistinct("ccaabbb") << endl;
    cout << solution.lengthOfLongestSubstringTwoDistinct("eceba") << endl;
    return 0;
}
