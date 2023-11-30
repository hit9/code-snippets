#include <string>
#include <unordered_map>

using namespace std;
class Solution {
   public:
    bool closeStrings(string word1, string word2) {
        if (word1.size() != word2.size()) return false;

        // 分别计数每个 ch 的多少
        unordered_map<char, int> m1;
        for (auto ch : word1) m1[ch]++;

        unordered_map<char, int> m2;
        for (auto ch : word2) {
            if (m1.find(ch) == m1.end()) return false;
            m2[ch]++;
        }

        // 反向计数, 数量为 x 的有几种 char
        unordered_map<int, int> t1;
        for (auto [k, v] : m1) t1[v]++;

        unordered_map<int, int> t2;
        for (auto [k, v] : m2) t2[v]++;

        return t1 == t2;
    }
};
