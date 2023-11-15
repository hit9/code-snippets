// https://leetcode.cn/problems/longest-common-prefix
// 14. 最长公共前缀
// 编写一个函数来查找字符串数组中的最长公共前缀。
// 如果不存在公共前缀，返回空字符串 ""。 输入：strs = ["flower","flow","flight"]
// 输出："fl"

#include <string>
#include <vector>
using namespace std;

// 分治做法

class Solution {
   public:
    // 两个字符串的最长公共前缀
    string longestCommonPrefixOfTwo(const string& a, const string& b) {
        string ans;
        for (int i = 0; i < a.size(); i++) {
            if (i < b.size() && a[i] == b[i])
                ans.push_back(a[i]);
            else
                break;
        }
        return ans;
    }
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0) return "";
        if (strs.size() == 1) return strs[0];
        if (strs.size() == 2) return longestCommonPrefixOfTwo(strs[0], strs[1]);
        // 二分
        vector<string> left;
        int i = 0;
        for (; i < strs.size() / 2; i++) left.push_back(strs[i]);
        vector<string> right;
        for (; i < strs.size(); i++) right.push_back(strs[i]);
        return longestCommonPrefixOfTwo(longestCommonPrefix(left),
                                        longestCommonPrefix(right));
    }
};
