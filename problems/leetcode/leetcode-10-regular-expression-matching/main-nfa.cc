#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 输入保证是小写字母, 这个 E 表示空字符
#define EPSILON 'E'

class Solution {
   public:
    // 状态号 state 0~N, 0 是起始状态, N 是终态
    // 跳转表 from state -> ch -> to state set
    using Table = unordered_map<int, unordered_map<char, unordered_set<int>>>;

    // 预处理 pattern 为 NFA, 返回终态标号 N 并填写好跳转表
    int compile(const string& p, Table& transitions) {
        int N = 0;

        for (int i = 0; i < p.size(); i++) {
            char ch = p[i];
            char prev;  // 上一个字符

            // 下一个是 '*' 则先跳过本轮处理
            if (i != p.size() - 1 && p[i + 1] == '*') continue;

            switch (ch) {
                case '*':
                    N++;
                    prev = p[i - 1];
                    if (prev == '.') {  // .*
                        for (auto c = 'a'; c <= 'z'; c++)
                            transitions[N][c].insert(N);
                    } else {
                        // a*
                        transitions[N][prev].insert(N);
                    }
                    // 添加空边跳转
                    transitions[N - 1][EPSILON].insert(N);
                    break;
                default:
                    // a-z 字母 或者 '.'
                    N++;
                    if (ch == '.') {
                        for (auto c = 'a'; c <= 'z'; c++)
                            transitions[N - 1][c].insert(N);
                    } else {
                        transitions[N - 1][ch].insert(N);
                    }
            }
        }
        return N;
    }

    // 不考虑空边的递归性，找目标状态集合
    unordered_set<int> findTargets(Table& transitions,
                                   unordered_set<int>& states, char ch) {
        unordered_set<int> targets;

        for (auto state : states) {
            if (transitions.find(state) == transitions.end()) continue;
            if (transitions[state].find(ch) == transitions[state].end())
                continue;
            // Copy targets
            targets.insert(transitions[state][ch].begin(),
                           transitions[state][ch].end());
        }
        return targets;
    }

    unordered_set<int> jump(Table& transitions, unordered_set<int>& states,
                            char ch) {
        // 可以直接经过 ch 到达的状态集合
        auto targets = findTargets(transitions, states, ch);
        // 可以经过一次空边到达的状态集合
        auto e = findTargets(transitions, states, EPSILON);
        if (!e.empty()) {
            // 继续递归, 然后合并
            auto e1 = jump(transitions, e, ch);
            targets.insert(e1.begin(), e1.end());
        }
        return targets;
    }

    bool isMatch(string s, string p) {
        Table transitions;

        auto N = compile(p, transitions);

        // 匹配 NFA, 从 {0} 起始
        // 不断更新可到达的状态集合，最终可以到达终态 N 算作成功
        unordered_set<int> states;
        states.insert(0);

        for (auto ch : s) {
            // 找到本次的可达状态列表
            auto targets = jump(transitions, states, ch);
            if (targets.empty()) return false;
            states = targets;
        }

        // 最后，还要兼容下空串的情况
        auto e = jump(transitions, states, EPSILON);
        if (!e.empty()) states.insert(e.begin(), e.end());

        // 必须包含终态
        if (states.find(N) != states.end()) return true;
        return false;
    }
};

int main(void) {
    Solution solution;
    cout << boolalpha << solution.isMatch("abc", "abc") << endl;       // true
    cout << boolalpha << solution.isMatch("abc", "abe") << endl;       // false
    cout << boolalpha << solution.isMatch("abc", "ab.") << endl;       // true
    cout << boolalpha << solution.isMatch("abc", "a.c") << endl;       // true
    cout << boolalpha << solution.isMatch("abc", "a.ce") << endl;      // false
    cout << boolalpha << solution.isMatch("abbbbbc", "ab*c") << endl;  // true
    cout << boolalpha << solution.isMatch("abbbbbe", "ab*c") << endl;  // false
    cout << boolalpha << solution.isMatch("abbbbbdef", "ab*c*def")
         << endl;                                                      // true
    cout << boolalpha << solution.isMatch("abc", ".*") << endl;        // true
    cout << boolalpha << solution.isMatch("abcdef", "ab..*") << endl;  // true
    cout << boolalpha << solution.isMatch("abcdef", "ab.*xyz")
         << endl;                                                       // false
    cout << boolalpha << solution.isMatch("ppi", "p*.") << endl;        // true
    cout << boolalpha << solution.isMatch("pp", "p*.") << endl;         // true
    cout << boolalpha << solution.isMatch("p", "p*.") << endl;          // true
    cout << boolalpha << solution.isMatch("ab", "*.c") << endl;         // false
    cout << boolalpha << solution.isMatch("aaba", "ab*a*c*a") << endl;  // false
    cout << boolalpha << solution.isMatch("aacccca", "ab*a*c*a")
         << endl;                                               // true
    cout << boolalpha << solution.isMatch("a", "ab*") << endl;  // true
    return 0;
}
