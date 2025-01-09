#include <iostream>
#include <string>

using namespace std;

class Solution {
    // 滑动窗口求最小覆盖子串 + dp
    // xxabcxxaxbcxx
    // 假设 dp[i] 表示阶段 s[...i] 子串上以 s[i] 字符结尾的合法子串的个数
    // 考虑下一阶段 s[...i+1], 即加入s[i+1] 时:
    // 1. 如果 s[i+1] 没有形成新的覆盖子串, 则 dp[i+1] += dp[i]
    //    因为原本 s[...i] 内的任何一个以 s[i] 结尾的合法子串, 加上 s[i+1]
    //    这个字符后, 都会形成一个以 s[...i+1] 结尾的新答案.
    // 2. 如果 s[i+1] 形成了一个新的覆盖子串, 则左端的收缩量就是 dp[i+1]
    //    的额外增量 . 因为原本的窗口无法完成覆盖, 现在可以覆盖了,
    //    那么额外产生的合法子串个数, 就是左端收缩的这一部分了.
    //    例如, 当 word2 = abc, word1 = xxxabc, R 到达 c 字符时恰好覆盖:
    //          xxxabc
    //        L ^   |
    //             L^     ----> L 前跳4步, 直到打破覆盖状态, 则新增了4个合法子串
    //               R
    // 最终答案等于 sum(dp[1] to dp[n])
   public:
    long long validSubstringCount(string word1, string word2) {
        // d2 记录 word2 的各个字符的出现次数
        // c2 记录 word2 的字符种类数
        int d2[26], c2 = 0;
        memset(d2, 0, sizeof(d2));
        for (auto ch : word2)
            if ((++d2[ch - 'a']) == 1) ++c2;

        // d1 记录 word1 当前窗口内的字符的出现次数
        // c1 记录 word1 当前窗口内 **满足的** 字符种类数
        int d1[26], c1 = 0;
        memset(d1, 0, sizeof(d1));

        int N = word1.size();

        long long dp[N];
        memset(dp, 0, sizeof(dp));

        // 以右端为主迭代滑动窗口 [L,R]
        // 要让闭区间 [L,R] 时刻处于无法覆盖的状态
        for (int L = 0, R = 0; R < N; ++R) {
            // 维护窗口右端, 如果满足了一个, c1 计数+1
            if ((++d1[word1[R] - 'a']) == d2[word1[R] - 'a']) ++c1;

            // 无论如何, 继承前一个 DP 值
            if (R > 0) dp[R] = dp[R - 1];

            // 已经满足的状态下, 左端收缩, 直到空区间,
            // 或左端卡在一个尚未满足的字符上, 或未知字符串上
            while (L <= R && c1 >= c2) {
                if ((--d1[word1[L] - 'a']) < d2[word1[L] - 'a']) --c1;
                ++L;
                // 走过多少个字符, dp 就加多少
                ++dp[R];
            }
        }

        long long ans = 0;
        for (int i = 0; i < N; ++i) ans += dp[i];
        return ans;
    }
};
