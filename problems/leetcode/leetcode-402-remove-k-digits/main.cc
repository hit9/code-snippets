// https://leetcode.cn/problems/remove-k-digits
// 402. 移掉 K 位数字

#include <deque>
#include <string>
using namespace std;

class Solution {
   public:
    string removeKdigits(string num, int k) {
        // 单调递增栈
        deque<char> s;

        for (auto ch : num) {
            // 先移除逆序大的
            while (k > 0 && !s.empty() && s.back() > ch) {
                k--;
                s.pop_back();
            }
            s.push_back(ch);
        }

        // 清理剩余元素, 移除右侧大的
        while (k > 0 && !s.empty()) {
            k--;
            s.pop_back();
        }

        // 输出结果
        std::string ans;
        bool finish_leading_zeros = false;

        while (!s.empty()) {
            auto ch = s.front();
            s.pop_front();

            // 跳过开头的 0
            if (ch == '0' && !finish_leading_zeros) continue;
            if (ch != '0') finish_leading_zeros = true;
            ans.push_back(ch);
        }

        // 避免空串返回
        return ans.size() ? ans : "0";
    }
};
