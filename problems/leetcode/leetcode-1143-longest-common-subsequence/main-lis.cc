// LCS 转化为 LIS 最长上升子序列来做
// 但是存在退化情况..
// 不过目前还是可以过 leetcode 测试的
// https://leetcode.cn/problems/longest-common-subsequence

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    int LIS(vector<int>& nums) {
        if (nums.size() == 0) return 0;

        vector<int> p;
        p.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > p.back())
                p.push_back(nums[i]);
            else {
                auto t = lower_bound(p.begin(), p.end(), nums[i]);
                *t = nums[i];
            }
        }
        return p.size();
    }
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();
        if (m > n) return longestCommonSubsequence(text2, text1);

        // text2 中每个字符在 text2 中出现的所有位置
        unordered_map<char, vector<int>> d;
        for (int i = 0; i < n; i++) d[text2[i]].push_back(i);

        // 制作一个数组
        // 把 text1 中每个字符替换其成在 text2 出现位置的逆序列, 拉平
        vector<int> nums;
        for (auto ch : text1)
            if (d.find(ch) != d.end())
                for (int j = d[ch].size() - 1; j >= 0; j--)
                    nums.push_back(d[ch][j]);

        return LIS(nums);
    }
};

int main(void) {
    Solution s;
    cout << s.longestCommonSubsequence("abcba", "abcbcba") << endl;
    cout << s.longestCommonSubsequence("acadfe", "abccadefe") << endl;
    return 0;
}
