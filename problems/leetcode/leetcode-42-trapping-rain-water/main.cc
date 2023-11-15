// https://leetcode.cn/problems/trapping-rain-water/description/?envType=study-plan-v2&envId=top-100-liked
// 42. 接雨水
// 给定 n 个非负整数表示每个宽度为 1
// 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。 输入：height =
// [0,1,0,2,1,0,1,3,2,1,2,1] 输出：6 解释：上面是由数组
// [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6
// 个单位的雨水（蓝色部分表示雨水）。
//
// 示例 2： 输入：height = [4,2,0,3,2,5] 输出：9


#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    int trap(vector<int>& height) {
        // 单调栈，存储下标
        // 从栈底到栈顶, height[s[i]] 递减
        // 栈顶最小
        stack<int> s;
        int ans = 0;

        for (auto i = 0; i < height.size(); i++) {
            // 栈顶最小，所以小于栈顶的元素，都要 pop 出来
            while (!s.empty() && height[s.top()] <= height[i]) {
                // 新的柱子更高，所以形成一个凹槽
                // 栈顶就是底部的高度, pop 出来
                //
                //             +-+
                //    +-+      | |
                //    | | h    | |
                //    | +- w --+ | bottom
                //    +----------+
                //    left      i
                int bottom = height[s.top()];
                s.pop();
                if (s.empty()) break;  // pop 后注意检查是否空
                // 目前的栈顶就是凹槽的左部分
                int left = s.top();
                // 新形成的雨水就是 h * w
                // 宽度 w = i - left - 1;
                // 高度 h = min(height[i], height[left]) - bottom
                ans += (min(height[i], height[left]) - bottom) * (i - left - 1);
            }
            s.push(i);
        }

        return ans;
    }
};

int main(void) {
    vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    Solution solution;
    cout << solution.trap(height) << endl;
    return 0;
}
