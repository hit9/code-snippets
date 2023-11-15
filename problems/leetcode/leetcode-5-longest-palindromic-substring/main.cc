// https://leetcode.cn/problems/longest-palindromic-substring
// 5. 最长回文子串
// 给你一个字符串 s，找到 s 中最长的回文子串。
// 如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。
//
// 输入：s = "babad" 输出："bab" 解释："aba" 同样是符合题意的答案。

// 思路: 前缀哈希 + 二分
// nlog(n)

#include <iostream>
#include <string>
#include <vector>

using namespace std;

using ull = unsigned long long;
const ull P = 131;

class Hash {
   private:
    int n;
    // h[i+1] 表示前缀 s[0..i]  (前闭后闭) 的哈希值
    // h[0] = 0
    vector<ull> h;
    vector<ull> p;

   public:
    explicit Hash(const string& s)
        : n(s.size()), h(vector<ull>(n + 1, 0)), p(vector<ull>(n + 1, 0)) {
        // 计算哈希数组
        p[0] = 1;  // power(P, 0) is 1
        for (int i = 1; i <= s.size(); i++) {
            h[i] = h[i - 1] * P + (s[i - 1] - 'a' + 1);
            p[i] = p[i - 1] * P;
        }
    }
    // 计算字符串区间 s[i..j] 的哈希值, 前闭后闭
    // 取前缀 A = h[j+1] 减去前缀 B = h[(i-1)+1]
    // 在 P 进制下，左移 B 和 A 左端对其，然后相减, 定义为 [i..j] 区间的哈希值
    // 即 A - B * (B << (j-i+1)) (p 进制下的左移，就是乘幂)
    // 要保证传入的 j >= i
    ull sub(int i, int j) { return h[j + 1] - h[i] * p[j - i + 1]; }
};

class Solution {
   public:
    string longestPalindrome(string s) {
        string s1("#");

        // 插入 '#' 消除奇偶问题
        for (auto ch : s) {
            s1.push_back(ch);
            s1.push_back('#');
        }

        int n = s1.size();

        // 正向前缀哈希
        Hash h1(s1);

        // 逆向前缀哈希
        string s2(s1.rbegin(), s1.rend());
        Hash h2(s2);

        // 对每个位置，二分从大到小查找以当前位置为中心的合适的回文子串的长度
        // 因为随着枚举的长度的变小，一旦 hash
        // 相等，再小也是会相等，所以可以二分
        //
        // +------------ N ----------------+
        // |             i                 |
        // # c # a # b # c # b # a # d # f #
        // 0 1 2 3 4 5 6 7
        //     +------ 2L+1 -------+
        //            max L=5
        //
        // 对于一个可能的长度 2L+1
        // 只需要判断: hash(s1[i-L..i-1]) 和 hash(s2[j-L..j-1]), 其中 j=n-i-1
        // 经过预处理后, 此时的 n 一定是奇数, L 的值不超过 min(n/2, i)

        int L = 0;  // 追踪最大的 L
        int I = 0;  // 追踪最大的 L 的时候的中心位置 i

        for (int i = 1; i < n - 1; i++) {
            int j = n - i - 1;

            // 从高向低，应用二分判定
            int low = 0;  // 长度的下限

            // 长度的上限, 不超过一半的总长度、不超过左和右侧部分
            int high = std::min({n / 2, i, j});

            while (low < high) {
                // 采用 +1 的形式的目的是为了考虑进去边界 high
                int mid = (low + high + 1) >> 1;

                if (h1.sub(i - mid, i - 1) != h2.sub(j - mid, j - 1)) {
                    // 说明枚举的长度太大了，需要继续严格减小
                    high = mid - 1;
                } else
                    // 相等的情况，可能是最长的长度、但也可能比较小，为了找最长的长度
                    // 可以把它提升为下界，继续向上二分找
                    low = mid;
            }
            // 终止时 low == high
            // 因为始终保证可行解在 [low, high]
            // 闭区间内，所以此时 low == high 就是保证哈希值相等的地方

            // 更新追踪的结果
            if (L < low) {
                L = low;
                I = i;
            }
        }

        // 找到那个最大的回文串
        // 由于提前做了预处理，那么需要把 '#' 剔除
        string ans;
        // 没有找到，那么取第一个 非 '#' 的
        for (int i = I - L; i <= I + L; i++)
            if (s1[i] != '#') ans.push_back(s1[i]);
        return ans;
    }
};

int main(void) {
    Solution solution;
    cout << solution.longestPalindrome("babad") << endl;
    cout << solution.longestPalindrome("cbbd") << endl;
    cout << solution.longestPalindrome("cabcbadf") << endl;
    cout << solution.longestPalindrome("abb") << endl;
    cout << solution.longestPalindrome("ab") << endl;
    return 0;
}
