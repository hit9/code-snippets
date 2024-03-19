#include <iostream>
#include <stack>
#include <vector>
using namespace std;
class Solution {
   public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();

        // 左右添加哨兵, 这样单调栈最终会清空
        nums.insert(nums.begin(), INT_MIN);
        nums.push_back(INT_MIN);

        // p[i] 表示 nums[i] 的下一个更小元素的位置
        // q[i] 表示 nums[i] 的上一个更小元素的位置
        vector<int> p(n + 2, 0), q(n + 2, 0);

        // s1, s2 是单调增栈, 存储下标
        stack<int> s1, s2;

        // 求下一个更小元素的位置
        for (int i = 0; i < n + 2; i++) {
            while (s1.size() && nums[s1.top()] > nums[i]) {
                p[s1.top()] = i;  // 下一个更小
                s1.pop();
            }
            s1.push(i);
        }

        // 求上一个更小元素的位置
        for (int i = n + 1; i >= 0; i--) {
            while (s2.size() && nums[s2.top()] > nums[i]) {
                q[s2.top()] = i;  // 上一个更小
                s2.pop();
            }
            s2.push(i);
        }

        // t[i] 表示 nums[i] 作为最小值时的数组长度
        // 需要数组经过 k+1
        vector<int> t(n + 2, 0);
        for (int i = 1; i <= n; i++)
            if (q[i] < k + 1 && k + 1 < p[i]) t[i] = p[i] - q[i] - 1;

        vector<int> ans(n + 2, 0);
        for (int i = 1; i <= n; i++) ans[i] = nums[i] * t[i];

        return *max_element(ans.begin(), ans.end());
    }
};
