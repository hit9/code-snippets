// https://leetcode.cn/problems/number-of-longest-increasing-subsequence
// 673. 最长递增子序列的个数
// 给定一个未排序的整数数组 nums ， 返回最长递增子序列的个数 。
// 注意 这个数列必须是 严格 递增的。
//
//
// 12ms 击败 99.24%使用 C++ 的用户
// https://leetcode.cn/problems/number-of-longest-increasing-subsequence/submissions/480514412/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// nlog(n) 时间复杂度，找出最长上升子序列的个数

class Solution {
   public:
    int findNumberOfLIS(vector<int>& nums) {
        // 各个列的桶, 每个桶存放元素的值
        vector<vector<int>> buckets;
        // 每一个桶的二分检索起点, 递进式二分
        vector<int> locs;
        // 前缀和桶， sums[k][j] 表示第 k 个桶上的 [0..j] 区间上的路径计数的总和
        vector<vector<int>> sums;
        // 辅助数组, 快照任一时刻各个桶的尾部元素, 辅助主迭代
        vector<int> p;

        // 放入头节点到第一个桶
        buckets.push_back({nums[0]});
        locs.push_back(0);
        sums.push_back({1});
        p.push_back(nums[0]);

        // 辅助函数, 给第 k 个桶放入一个新元素
        // 并同步计算路径总数, 时间复杂度 log(n)
        auto push = [&](int k, int num) {
            // 找到上一个桶中严格小于 num 的项，然后把计数累加起来
            // 如果是第 0 个桶，count 初始化为 1
            int count = 1;

            if (k >= 1) {
                // 需要注意的是 buckets 数组的尾部才是桶顶
                // buckets[k] 都是递减排列的;
                // 本次 loc 可以作为下次的二分起点
                // 所谓，维护 loc 数组以递进式二分
                int k1 = k - 1;
                auto& b1 = buckets[k1];
                int loc = upper_bound(b1.begin() + locs[k1], b1.end(), num,
                                      greater<int>()) -
                          b1.begin();
                locs[k1] = loc;  // 更新上一个桶的检索节点

                // 前一个桶的区间 [0..loc] 的 count 总和
                // 即区间 [loc, n) 的 (总和 - 前缀和)
                auto total = sums[k1][buckets[k1].size() - 1];

                // 区间  [0.. loc-1] 的计数和::
                // 如果 loc 是 0 , 则相当于区间 [loc, n) 上是求总和
                auto sum_before_loc = loc > 0 ? sums[k1][loc - 1] : 0;
                count = total - sum_before_loc;
            }

            buckets[k].push_back(num);
            p[k] = num;  // 更新辅助数组

            // 更新前缀和
            auto sum = count;
            if (!sums[k].empty()) sum += sums[k][sums[k].size() - 1];
            sums[k].push_back(sum);
        };

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > p[p.size() - 1]) {
                // 扩展桶列表, 扩展辅助数组
                buckets.push_back({});
                sums.push_back({});
                locs.push_back(0);  // 初始化其检索起点 0
                p.push_back(0);
                // 推入此元素到这个新桶
                push(buckets.size() - 1, nums[i]);
            } else {
                // 查找合适的桶放入新元素
                int k = lower_bound(p.begin(), p.end(), nums[i]) - p.begin();
                push(k, nums[i]);
            }
        }

        // 最长上升序列的个数，就是最后一个桶中所有元素的路径数的总和
        const auto& last = sums[sums.size() - 1];
        return last[last.size() - 1];
    }
};

int main(void) {
    vector<int> nums{2, 4, 3, 5, 4, 7, 2};
    Solution s;
    cout << s.findNumberOfLIS(nums) << endl;
    return 0;
}
