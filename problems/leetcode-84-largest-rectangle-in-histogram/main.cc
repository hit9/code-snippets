// https://leetcode.cn/problems/largest-rectangle-in-histogram/description/?envType=study-plan-v2&envId=top-100-liked
// 84. 柱状图中最大的矩形
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为
// 1 。 求在该柱状图中，能够勾勒出来的矩形的最大面积。

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();

        // s 是单调栈，存储下标，始终保证 top 的高度最大
        stack<int> s;

        int m = 0;  // 追踪最大面积

        auto handle = [&](int i) {
            // 要弹出的矩形: 计算以此为高度的矩形的面积
            auto j = s.top();
            s.pop();

            // 当前矩形 j 右侧的面积 (包括自身, 不包括矩形 i)
            auto R = (i - j) * heights[j];
            // 当前矩形左侧的面积, 不包括自身
            // 如果左侧没有更低的矩形了，面积会更大，宽度为 j
            auto L = (s.empty() ? j : (j - 1 - s.top())) * heights[j];

            // 以 heights[j] 为高的矩形面积
            m = std::max(m, R + L);
        };

        for (auto i = 0; i < n; i++) {
            auto h = heights[i];
            while (!s.empty() && heights[s.top()] > h) handle(i);
            s.push(i);
        }
        // 如果栈内还有元素，要弹出来处理完
        while (!s.empty()) handle(n);
        return m;
    }
};

int main(void) {
    Solution solution;
    vector<int> heights{2, 1, 0, 2};
    cout << solution.largestRectangleArea(heights) << endl;
    return 0;
}
