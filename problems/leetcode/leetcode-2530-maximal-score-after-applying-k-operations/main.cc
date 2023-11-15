// https://leetcode.cn/problems/maximal-score-after-applying-k-operations/description/?envType=daily-question&envId=2023-10-18
// 2530. 执行 K 次操作后的最大分数
// 给你一个下标从 0 开始的整数数组 nums 和一个整数 k 。你的 起始分数 为 0 。
//
// 在一步 操作 中：
//
//    选出一个满足 0 <= i < nums.length 的下标 i ，
//    将你的 分数 增加 nums[i] ，并且
//    将 nums[i] 替换为 ceil(nums[i] / 3) 。
//
// 返回在 恰好 执行 k 次操作后，你可能获得的最大分数。
//
// 向上取整函数 ceil(val) 的结果是大于或等于 val 的最小整数。

#include <cmath>
#include <queue>
#include <vector>
using namespace std;

// 思路: 贪婪
// 每次取最大值来上分
// 用优先级队列来维护最大值

class Solution {
   public:
    long long maxKelements(vector<int>& nums, int k) {
        priority_queue<int> q;
        for (auto v : nums) q.push(v);

        long long ans = 0;
        for (auto i = 0; i < k; i++) {
            auto v = q.top();
            ans += v;
            q.pop();
            q.push(int(ceil(v / 3.0)));
        }

        return ans;
    }
};
