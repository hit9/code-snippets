#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
class Solution {
   public:
    string minWindow(string s, string t) {
        unordered_map<char, int> d1;  // t 内的字符频次计数
        int c = 0;  // 还需要统计的字符种类, 初始化为 t 中的字符种类
        for (auto ch : t) {
            d1[ch]++;
            if (d1[ch] == 1) c++;
        }
        unordered_map<char, int> d2;  // 窗口内的字符频次计数
        int ans_L = 0, ans_size = 0x3f3f3f3f;
        for (int L = 0, R = 0; R < s.size(); R++) {
            // 维护右端: 窗口内计数+1
            // 并且如果是需要的字符, 则维护需要的种类 c
            if (++d2[s[R]] == d1[s[R]]) c--;
            // 维护左端: 左端 L 字符的出现次数超过 t 中的
            while (L < R && d2[s[L]] > d1[s[L]]) d2[s[L++]]--;
            // 维护答案
            if (c == 0 && ans_size > (R - L + 1)) {
                ans_L = L;
                ans_size = R - L + 1;
            }
        }
        if (ans_size > s.size()) return "";
        return s.substr(ans_L, ans_size);
    }
};

int main(void) {
    string s("acbbaca");
    string t("aba");
    Solution sl;
    cout << sl.minWindow(s, t) << endl;
    return 0;
}
