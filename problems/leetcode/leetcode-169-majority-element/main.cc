// https://leetcode.cn/problems/majority-element/description/?envType=study-plan-v2&envId=top-100-liked
// 169. 多数元素
// 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
// 你可以假设数组是非空的，并且给定的数组总是存在多数元素。
// 进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。

#include <vector>
using namespace std;
class Solution {
   public:
    int majorityElement(vector<int>& nums) {
        // moore 投票算法
        // 因为有一个元素出现次数超过 n/2
        // 此元素的票可以和其他元素抵消，最终胜出
        // 也就是说这个众数的票数永远不可能到达 0

        // 当前 num 的票
        int vote = 0;
        // 当前考察的候选数字
        int v = 0;

        for (auto i = 0; i < nums.size(); i++) {
            // 更换候选数字
            if (vote == 0) v = nums[i];
            // 如果相等，则继续加票
            // 否则减票
            if (nums[i] == v)
                vote++;
            else
                vote--;
        }
        return v;
    }
};
