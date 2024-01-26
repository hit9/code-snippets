// https://leetcode.cn/problems/132-pattern/
// 456. 132 模式
// 给你一个整数数组 nums ，数组中共有 n 个整数。132 模式的子序列 由三个整数
// nums[i]、nums[j] 和 nums[k] 组成，并同时满足：i < j < k 和 nums[i] < nums[k]
// < nums[j] 。 如果 nums 中存在 132 模式的子序列 ，返回 true ；否则，返回 false
// 。
//
// 例子: 输入：nums = [1,2,3,4] 输出：false 解释：序列中不存在 132
// 模式的子序列。
//
// 例子: 输入：nums = [3,1,4,2] 输出：true 解释：序列中有 1 个 132
// 模式的子序列： [1, 4, 2] 。
//
// 例子: 输入：nums = [-1,3,2,0] 输出：true 解释：序列中有 3 个 132
// 模式的的子序列：[-1, 3, 2]、[-1, 3, 0] 和 [-1, 2, 0] 。

// https://writings.sh/post/monotonic-stack#132%E6%A8%A1%E5%BC%8F

#include <stack>
#include <vector>
using namespace std;
class Solution {
   public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return false;

        // L[i] 表示 i 左边（不包括i）的最小值, 也就是要找的 1
        vector<int> L(n, INT_MAX);
        for (int i = 1; i < n; i++) L[i] = std::min(L[i - 1], nums[i - 1]);

        // s 存的是元素的值, 单调递减栈
        stack<int> s;

        // 从右侧向左找
        for (int i = n - 1; i >= 1; i--) {
            if (nums[i] > L[i]) {
                while (!s.empty()) {
                    if (s.top() <= L[i])
                        // 比 L[i] 小的, 这部分会被先弹出去，因为是递减栈
                        s.pop();
                    else if (s.top() == nums[i])  // 等于 nums[i] 的
                        s.pop();
                    else if (s.top() < nums[i])  // 大于 L[i], 但是严格小于
                                                 // nums[i] 的，找到 132 模式
                        return true;
                    else  // 无元素可以 pop, break
                        break;
                }
                s.push(nums[i]);
            }
        }
        return false;
    }
};
