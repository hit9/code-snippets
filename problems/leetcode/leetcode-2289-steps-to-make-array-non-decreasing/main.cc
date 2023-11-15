#include <stack>
#include <vector>
using namespace std;
class Solution {
   public:
    int totalSteps(vector<int>& nums) {
        stack<int> s;  // 存储下标, 从右向左，最小栈
        int ans = 0;   // 所有步数中最大的就是总步数

        // 记录被第 i 个位置连续弹出的数量
        vector<int> steps(s.size(), 0);
        for (int i = nums.size() - 1; i >= 0; i--) {
            //              [7, 14, 4, 14, 12, 2, 6, 13]
            // 第1次消除            4      12  2
            // 第2次消除                       6
            // 第3次消除                             13
            // 从右向左看，递减栈的弹出规律:
            // 选用从右向左的递减栈的原因是，第一个 7 必须最终是全局最小。
            //
            //              [7, 14, 4, 14, 12, 2, 6, 13]      事后栈内
            //              (栈低在右)
            // 第1次弹出                   12 [2, 6]           [12,13]
            // 第2次弹出               14 [12,       13]       [14]
            // 第3次弹出        14 [4]                         [14,14]
            //                                                 [7,14,14]
            // 要求的步数，其实是左边的大的数，连续弹出小的数的最大深度。
            // 比如说，第一次消除，取的是各个弹出列表的第一项 4, 12, 2
            // 但是第二次消除，没办法直接消除第二层的 6 和 13
            // 因为 14 必须要先消除 6，才可以轮到 13.
            while (!s.empty() && nums[s.top()] < nums[i]) {
                // 当前位置被弹出的数量要考虑要被弹出的这个元素拦截过的小元素的数量
                // 比如说 14 要弹出 13 的时候，13 已经拦截了 2,6 两个元素
                steps[i] = std::max(steps[s.top()] + 1, steps[i]);
                s.pop();
            }
            ans = std::max(ans, steps[i]);
            s.push(i);
        }
        return ans;
    }
};
