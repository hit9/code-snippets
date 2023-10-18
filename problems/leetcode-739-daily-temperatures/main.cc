// https://leetcode.cn/problems/daily-temperatures/description/?envType=study-plan-v2&envId=top-100-liked
// 739. 每日温度
// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。
//
// 示例 1: 输入: temperatures = [73,74,75,71,69,72,76,73] 输出: [1,1,4,2,1,1,0,0]
//
// 示例 2: 输入: temperatures = [30,40,50,60] 输出: [1,1,1,0]
//
// 示例 3: 输入: temperatures = [30,60,90] 输出: [1,1,0]


#include <stack>
#include <vector>

using namespace std;
class Solution {
   public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> s;
        int n = temperatures.size();

        vector<int> ans(n, 0);

        for (auto i = 0; i < temperatures.size(); i++) {
            while (!s.empty() && temperatures[s.top()] < temperatures[i]) {
                auto j = s.top();
                s.pop();
                ans[j] = i - j;
            }
            s.push(i);
        }
        return ans;
    }
};
