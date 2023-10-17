// https://leetcode.cn/problems/longest-valid-parentheses/discussion/?envType=study-plan-v2&envId=top-100-liked
// 32. 最长有效括号
// 给你一个只包含 '(' 和 ')'
// 的字符串，找出最长有效（格式正确且连续）括号子串的长度。
//
// 示例 1： 输入：s = "(()" 输出：2 解释：最长有效括号子串是 "()"
//
// 示例 2： 输入：s = ")()())" 输出：4 解释：最长有效括号子串是 "()()"
//
// 示例 3： 输入：s = "" 输出：0

#include <stack>
#include <string>
using namespace std;

class Solution {
   public:
    int longestValidParentheses(string s) {
        // k 是存放没有正确匹配的坐标断点
        stack<int> k;

        for (auto i = 0; i < s.size(); i++) {
            // 括号匹配则出栈
            if (s[i] == ')' && !k.empty() && s[k.top()] == '(') {
                k.pop();
                continue;
            }
            // 否则其下标入栈
            k.push(i);
        }

        // k 中记录的是无法形成有效括号串的所有断点坐标

        // 不存在断点，则全部字符串合法
        if (k.empty()) return s.size();

        // 找到断点的最大区间长度, 从右往左找
        // 用 r 来跟进右侧坐标
        int r = s.size();

        // n 来跟进最大的区间长度
        int n = 0;
        while (!k.empty()) {
            auto i = k.top();
            auto d = r - i - 1;
            if (n < d) n = d;
            r = i;
            k.pop();
        }
        // 全部 pop 完后，要再看下到起点的距离
        if (r > n) return r;

        return n;
    }
};
