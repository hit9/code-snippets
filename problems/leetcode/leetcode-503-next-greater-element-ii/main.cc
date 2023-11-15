// https://leetcode.cn/problems/next-greater-element-ii/
// 503. 下一个更大元素 II

#include <stack>
#include <vector>
using namespace std;
class Solution {
   public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> s;  // 递减栈、存储下标
        for (int i = 0; i < n + n - 1; i++) {
            while (!s.empty() && nums[s.top()] < nums[i % n]) {
                if (ans[s.top()] == -1) ans[s.top()] = nums[i % n];
                s.pop();
            }
            s.push(i % n);
        }
        return ans;
    }
};
