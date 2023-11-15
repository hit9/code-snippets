// https://leetcode.cn/problems/longest-nice-substring
//
// 1763. 最长的美好子字符串
// 当一个字符串 s 包含的每一种字母的大写和小写形式 同时 出现在 s
// 中，就称这个字符串 s 是 美好 字符串。比方说，"abABB" 是美好字符串，因为 'A'
// 和 'a' 同时出现了，且 'B' 和 'b' 也同时出现了。然而，"abA" 不是美好字符串因为
// 'b' 出现了，而 'B' 没有出现。
// 给你一个字符串 s ，请你返回 s 最长的 美好子字符串 。如果有多个答案，请你返回
// 最早 出现的一个。如果不存在美好子字符串，请你返回一个空字符串。
//
// 输入：s = "YazaAay"
// 输出："aAa"
// 解释："aAa" 是一个美好字符串，因为这个子串中仅含一种字母，其小写形式 'a'
// 和大写形式 'A' 也同时出现了。 "aAa" 是最长的美好子字符串。
//
// 这个题不是很简单，题解:
// https://leetcode.cn/problems/longest-nice-substring/solutions/2501255/yi-dao-bu-jian-dan-de-jian-dan-ti-cai-yo-y88k/

#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
using namespace std;
class Solution {
   public:
    char mirror(char ch) {
        if (isupper(ch)) return tolower(ch);
        return toupper(ch);
    }

    // pre 记录上一次其对称字符出现的位置. 默认是 -1;
    vector<int> make_pre(string& s) {
        // m 记录一个字符最近出现的位置
        unordered_map<char, int> m;
        vector<int> pre(s.size(), -1);

        for (int i = 0; i < s.size(); i++) {
            m[s[i]] = i;  // 当前位置，一个字符在左边出现的最新位置
            auto mch = mirror(s[i]);  // 镜像字符
            if (m.find(mch) != m.end()) {
                pre[i] = m[mch];
            }
        }
        return pre;
    }

    vector<int> make_post(string& s) {
        // m 记录一个字符最近出现的位置 (从右向左扫)
        unordered_map<char, int> m;
        vector<int> post(s.size(), s.size());

        for (int i = s.size() - 1; i >= 0; --i) {
            m[s[i]] = i;  // 当前位置，一个字符在左边出现的最新位置
            auto mch = mirror(s[i]);  // 镜像字符
            if (m.find(mch) != m.end()) {
                post[i] = m[mch];
            }
        }
        return post;
    }

    string longestNiceSubstring(string s) {
        int n = s.size();

        auto pre = make_pre(s);
        auto post = make_post(s);

        auto [L, R] = dfs(s, 0, n, pre, post);
        return s.substr(L, R - L);
    }

    // L 左闭合、R 右开
    // 返回 s 在区间 [L,R) 上的最大的美好字符串的区间
    std::pair<int, int> dfs(string& s, int L, int R, vector<int>& pre,
                            vector<int>& post) {
        int i = L;  // 从左到右搜索每个断点
        int length = -1;

        // 要找到的 left 和 right
        int left, right;

        while (i < R) {
            // 镜像字符不在  [L, R) 范围内, 也就是 i 处是个断点
            if (pre[i] < L && post[i] >= R) {
                // 到 [L, i) 区间上去找
                auto [l, r] = dfs(s, L, i, pre, post);

                // 如果找到的美好字符串的区间比较大，则更新结果
                // 要返回最左的，那么惰性更新，只有更大时，才更新
                if (r - l > length) {
                    left = l;
                    right = r;
                    length = right - left;
                }

                // L 跳到下一个非断点处，继续扫描
                L = i + 1;
            }
            i++;
        }

        // 最后的个区间，此时 i 到达 R; L 是最后一个断点
        // 如果找不到任何断点, length 维持 -1, L 维持原始值，会最终返回 {L, R}
        if (R - L > length) {
            left = L;
            right = R;
        }

        return {left, right};
    }
};
