// https://leetcode.cn/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/description/
// 138. 有效数字
// 有效数字（按顺序）可以分成以下几个部分：
//    1. 若干空格
//    2. 一个 小数 或者 整数
//    3. （可选）一个 'e' 或 'E' ，后面跟着一个 整数
//    4. 若干空格
// 小数（按顺序）可以分成以下几个部分：
//    1. （可选）一个符号字符（'+' 或 '-'）
//    2. 下述格式之一：
//        至少一位数字，后面跟着一个点 '.'
//        至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
//        一个点 '.' ，后面跟着至少一位数字
// 整数（按顺序）可以分成以下几个部分：
//    1.（可选）一个符号字符（'+' 或 '-'）
//    2. 至少一位数字
// 部分有效数字列举如下：["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10",
// "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"]
// 部分无效数字列举如下：["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3",
// "95a54e53"] 给你一个字符串 s ，如果 s 是一个 有效数字 ，请返回 true 。 示例
// 1： 输入：s = "0" 输出：true 示例 2： 输入：s = "e" 输出：false 示例 3：
// 输入：s = "." 输出：false

#include <iostream>
#include <string>

using namespace std;

bool isnum(char ch) { return ch >= '0' && ch <= '9'; }

int jump(int state, char ch, bool is_end) {
    switch (state) {
        case 0:
            switch (ch) {
                case ' ':
                    return 0;
                case '+':
                case '-':
                    return 1;
                case '.':
                    return 4;
                default:
                    if (isnum(ch)) return 2;
                    return 99;
            }
        case 1:
            switch (ch) {
                case '.':
                    return 4;
                default:
                    if (isnum(ch)) return 2;
                    return 99;
            }
        case 2:
            if (is_end) return 9;
            switch (ch) {
                case '.':
                    return 7;
                case 'e':
                case 'E':
                    return 5;
                case ' ':
                    return 8;
                default:
                    if (isnum(ch)) return 2;
                    return 99;
            }
        case 3:
            if (is_end) return 9;
            switch (ch) {
                case 'e':
                case 'E':
                    return 5;
                case ' ':
                    return 8;
                default:
                    if (isnum(ch)) return 3;
                    return 99;
            }
        case 4:
            if (isnum(ch)) return 3;
            return 99;
        case 5:
            switch (ch) {
                case '+':
                case '-':
                    return 10;
                default:
                    if (isnum(ch)) return 6;
                    return 99;
            }
        case 6:
            if (is_end) return 9;
            if (isnum(ch))
                return 6;
            else if (ch == ' ')
                return 8;
            return 99;
        case 7:
            if (is_end) return 9;
            switch (ch) {
                case ' ':
                    return 8;
                case 'e':
                case 'E':
                    return 5;
                default:
                    if (isnum(ch)) return 3;
                    return 99;
            }
        case 8:
            if (is_end) return 9;
            if (ch == ' ') return 8;
            return 99;
        case 10:
            if (isnum(ch)) return 6;
            return 99;
        default:
            return 99;
    }
}

class Solution {
   public:
    bool validNumber(string s) {
        int state = 0;
        for (int i = 0; i < s.size(); i++) {
            auto ch = s[i];
            state = jump(state, ch, false);
            if (state == 99) return false;
        }
        state = jump(state, '\0', true);
        if (state == 9) return true;
        return false;
    }
};

int main() {
    Solution solution;
    cout << solution.validNumber(" +1234.323e333 ") << endl;
    cout << solution.validNumber(" + ") << endl;
    cout << "有效:" << endl;
    string examples1[] = {"2",    "0089",  "-0.1",    "+3.14",
                          "4.",   "-.9",   "2e10",    "-90E3",
                          "3e+7", "+6e-1", "53.5e93", "-123.456e789"};
    for (auto& s : examples1) {
        cout << solution.validNumber(s) << endl;
    }
    cout << "无效:" << endl;
    string examples2[] = {"abc",    "1a",  "1e",  "e3",
                          "99e2.5", "--6", "-+3", "95a54e53"};
    for (auto& s : examples2) {
        cout << solution.validNumber(s) << endl;
    }
    return 0;
}
