#include <algorithm>
#include <vector>
using namespace std;

// 贪心

class Solution {
   public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // 按区间右端排序, 次要按左端排序
        sort(intervals.begin(), intervals.end(),
             [&](const auto& a, const auto& b) {
                 return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
             });

        // e 记录合法结果的最右端
        // 每次发生重叠时, 考虑移除更靠右的区间
        int ans = 0, e = intervals[0][1];
        // 枚举区间右端
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < e) {  // 发生重叠
                ans++;                  // 移除最右端的
            } else {                    // 无重叠
                e = intervals[i][1];
            }
        }
        return ans;
    }
};
