// https://leetcode.cn/problems/longest-common-prefix
// 14. 最长公共前缀
// 编写一个函数来查找字符串数组中的最长公共前缀。
// 如果不存在公共前缀，返回空字符串 ""。 输入：strs = ["flower","flow","flight"]
// 输出："fl"

#include <string>
#include <vector>
using namespace std;

// 动规做法

class Solution {
   public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        if (n == 0) return 0;

        // dp[i] 表示 [..i] 上的最长公共前缀的长度
        // 无需数组，直接递推就可以
        int dp = strs[0].size();

        for (int i = 1; i < n; i++) {
            int j = 0;
            for (; j < dp && j < strs[i].size() && strs[0][j] == strs[i][j];
                 j++)
                ;
            dp = j;
        }

        return strs[0].substr(0, dp);
    }
};
