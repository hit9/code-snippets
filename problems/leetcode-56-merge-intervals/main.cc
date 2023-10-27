// https://leetcode.cn/problems/merge-intervals/
//
// 56. 合并区间
//
// 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti,
// endi] 。请你合并所有重叠的区间，并返回
// 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
//
// 示例 1： 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
// 输出：[[1,6],[8,10],[15,18]] 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为
// [1,6].
//
// 示例 2： 输入：intervals = [[1,4],[4,5]] 输出：[[1,5]] 解释：区间 [1,4] 和
// [4,5] 可被视为重叠区间。

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // 先按照左边排序
        sort(intervals.begin(), intervals.end(),
             [](const auto& a, const auto& b) { return a[0] < b[0]; });

        // 再合并
        vector<vector<int>> ans;

        int L =
            intervals[0]
                     [0];  // 以左边为主来滑动，表示当前要处理的区间的左侧端点
        int R =
            intervals[0][1];  // 以当前 L 为左端点可以向右连续到达的最长的右端点

        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= R) {
                // 和当前区间有重叠，则扩展 R
                R = std::max(R, intervals[i][1]);
            } else {
                // 和当前区间无重叠，则输出当前结果，开始下一个区间
                ans.push_back({L, R});
                L = intervals[i][0];
                R = intervals[i][1];
            }
        }

        // 注意把最后一个 push 进去
        ans.push_back({L, R});
        return ans;
    }
};
