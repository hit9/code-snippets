// https://leetcode.cn/problems/number-of-longest-increasing-subsequence
// 673. 最长递增子序列的个数
// 给定一个未排序的整数数组 nums ， 返回最长递增子序列的个数 。
// 注意 这个数列必须是 严格 递增的。

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// nlog(n) 时间复杂度，找出最长上升子序列的个数

class Solution {
   public:
    // 升序数组，二分找恰好 < x 的位置
    int bs1(const vector<int>& nums, int x) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == x)
                return mid;
            else if (nums[mid] < x)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }

    // 降序数组，二分查找右侧严格 <x 的起点位置
    int bs2(const vector<int>& nums, int x) {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < x)
                right = mid;
            else
                left = mid + 1;
        }
        return right;
    }

    int findNumberOfLIS(vector<int>& nums) {
        // 各个列的桶
        vector<vector<int>> buckets;
        // 追踪序列数目的桶列表, counts[k][j] 表示第 k
        // 个桶上可以到达第 j 个元素路径总数
        vector<vector<int>> counts;
        // 辅助数组, 快照任一时刻各个桶的尾部元素
        vector<int> p;

        // 放入头节点到第一个桶
        buckets.push_back({nums[0]});
        counts.push_back({1});
        p.push_back(nums[0]);

        // 辅助函数, 给第 k 个桶放入一个新元素
        // 并同步计算路径总数, 时间复杂度 log(n)
        auto push = [&](int k, int num) {
            // 找到上一个桶中严格小于 num 的项，然后把计数累加起来
            // 如果是第 0 个桶，count 初始化为 1
            int count = 0;

            if (k >= 1) {
                // 需要注意的是 buckets 数组的尾部才是桶顶
                // buckets[k] 都是递减排列的
                for (auto j = bs2(buckets[k - 1], num);
                     j < buckets[k - 1].size(); j++)
                    count += counts[k - 1][j];
            } else {
                count = 1;
            }

            counts[k].push_back(count);
            buckets[k].push_back(num);
            p[k] = num;  // 更新辅助数组
        };

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > p[p.size() - 1]) {
                // 扩展桶列表, 扩展辅助数组
                buckets.push_back({});
                counts.push_back({});
                p.push_back(0);
                // 推入此元素到这个新桶
                push(buckets.size() - 1, nums[i]);
            } else {
                // 查找合适的桶放入新元素
                int k = bs1(p, nums[i]);
                push(k, nums[i]);
            }
        }

        // 最长上升序列的个数，就是最后一个桶中所有元素的路径数的总和
        auto& last = counts[counts.size() - 1];
        return accumulate(last.begin(), last.end(), 0);
    }
};

int main(void) {
    vector<int> nums{2, 4, 3, 5, 4, 7, 2};
    Solution s;
    cout << s.findNumberOfLIS(nums) << endl;
    return 0;
}
