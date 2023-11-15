// https://leetcode.cn/problems/russian-doll-envelopes
// 354. 俄罗斯套娃信封问题
// 给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i
// 个信封的宽度和高度。
// 当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
// 请计算 最多能有多少个
// 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
// 注意：不允许旋转信封。

// 母问题: LIS 问题

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class Solution {
   public:
    int maxEnvelopes(vector<vector<int>>& es) {
        int n = es.size();

        // 先优先按 w 排序
        sort(es.begin(), es.end(), [](const auto& a, const auto& b) {
            // 如果 w 相同，h 则逆序
            // 这里非常巧妙，逆序过来之后，相同的 w 情况下保证 LIS 求解最多取 1
            // 个
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });

        vector<int> p;  // h 升序排列的辅助数组
        p.push_back(es[0][1]);

        for (int i = 1; i < n; i++) {
            auto num = es[i][1];
            if (num > p.back())
                p.push_back(num);
            else {
                auto t = lower_bound(p.begin(), p.end(), num);
                *t = num;
            }
        }

        return p.size();
    }
};

int main(void) {
    Solution s;
    vector<vector<int>> es{{15, 8},  {2, 20},  {2, 14},  {4, 17},  {8, 19},
                           {8, 9},   {5, 7},   {11, 19}, {8, 11},  {13, 11},
                           {2, 13},  {11, 19}, {8, 11},  {13, 11}, {2, 13},
                           {11, 19}, {16, 1},  {18, 13}, {14, 17}, {18, 19}};
    cout << s.maxEnvelopes(es) << endl;
    return 0;
}
