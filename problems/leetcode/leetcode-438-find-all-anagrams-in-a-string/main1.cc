#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 优化版
class Solution {
   public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> d;  // p 中的各个字符的出现次数
        int a = 0;                   // p 中不同的字符个数
        for (auto ch : p)
            if (++d[ch] == 1) a++;
        int b = 0;  // b 是窗口内的扣减了 p 中字符的种类数
        vector<int> ans;
        for (int L = 0, R = 0; R < s.size(); R++) {
            // 扣减出现频次, 并且, 如果扣减后是 0 , 则记录一次 b
            if (--d[s[R]] == 0) b++;
            // 恢复出现频次, 如果恢复前是 0, 则也要恢复 b
            while (L < R && R - L + 1 > p.size())
                if (++d[s[L++]] == 1) b--;
            if (a == b) ans.push_back(L);
        }
        return ans;
    }
};
