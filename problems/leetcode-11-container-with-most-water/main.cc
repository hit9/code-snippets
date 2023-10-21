// https://leetcode.cn/problems/container-with-most-water/
// 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
// 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
// 返回容器可以储存的最大水量。
#include <algorithm>
#include <vector>
using namespace std;
class Solution {
   public:
    // 面积取决于短的板
    // S = min(height[i], height[j]) * (j-i)
    // 如果移动短板，新的 min(height[i], height[j]) 可能会增大, 面积才有可能增大
    // 否则，移动长板，新的 min(height[i], height[j]) 不变 (长板变长) 或者
    // (长板变短板) 变小，而且宽度减一，面积一定减小
    // 所以，结论就是，只需要每一次移动短板，来搜最大面积
    int maxArea(vector<int>& height) {
        int ans = 0;
        for (int i = 0, j = height.size() - 1; i < j;) {
            ans = std::max((j - i) * std::min(height[i], height[j]), ans);
            if (height[i] < height[j])
                i++;
            else
                j--;
        }
        return ans;
    }
};
