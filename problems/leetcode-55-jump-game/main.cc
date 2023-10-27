// https://leetcode.cn/problems/jump-game
// 55. 跳跃游戏
// 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标
// 。数组中的每个元素代表你在该位置可以跳跃的最大长度。
// 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
//
// 示例 1： 输入：nums = [2,3,1,1,4] 输出：true 解释：可以先跳 1 步，从下标 0
// 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
//
// 示例 2： 输入：nums =
// [3,2,1,0,4] 输出：false 解释：无论怎样，总会到达下标为 3
// 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。

#include <vector>
using namespace std;

// 向右找到最远可以跳到的位置
// 可以覆盖到最后一个位置时停止
class Solution {
   public:
    bool canJump(vector<int>& nums) {
        // R 是当前可以跳到的最靠右的位置
        int R = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (R < i) return false;  // 前面最远也到不了 i，就无法向后跳跃了
            R = std::max(i + nums[i], R);  // 更新最远可以跳到的位置
            if (R >= nums.size() - 1) return true;
        }
        return false;
    }
};
