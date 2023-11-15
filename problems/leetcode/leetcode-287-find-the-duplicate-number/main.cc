// https://leetcode.cn/problems/find-the-duplicate-number/description/?envType=study-plan-v2&envId=top-100-liked
// 287. 寻找重复数
// 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和
// n），可知至少存在一个重复的整数。 假设 nums 只有 一个重复的整数 ，返回
// 这个重复的数 。 你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1)
// 的额外空间。
// 1 <= n <= 10^5
// nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次
//
// 示例 1： 输入：nums = [1,3,4,2,2] 输出：2
//
// 示例 2： 输入：nums = [3,1,3,4,2] 输出：3
//
// 采用链表查环算法（龟兔算法），快慢指针，快指针2步、慢指针1步
// 每个元素的值，就是下个节点的位置
// 例如 nums = [3,1,3,4,2]  的时候，第一个元素 nums[0] 的 next 节点是 nums[3]

#include <vector>
using namespace std;

class Solution {
   public:
    int findDuplicate(vector<int>& nums) {
        int fast = 0, slow = 0;
        int n = nums.size();
        // p 是 [0,n) 范围内的
        // nums 的元素是 [1,n-1] 范围内的, 所以不会崩索引
        auto next = [&](int p) { return nums[p]; };

        while (fast < n && slow < n) {
            fast = next(next(fast));
            slow = next(slow);
            if (slow == fast) break;
        }

        // 找环的入口, 起一个新的指针 p 在头节点
        // p 设置为相遇处 slow
        int q = 0, p = slow;
        // 各自走一步，再次相遇，就是入口
        while (p < n && q < n) {
            // 相遇点就是环的入口
            // 但是注意，nums[p] 表示的是下一个节点的位置
            // 我们要返回重复的数，所以是当前的 p 本身
            if (p == q) return p;
            p = next(p);
            q = next(q);
        }
        return 0;
    }
};
