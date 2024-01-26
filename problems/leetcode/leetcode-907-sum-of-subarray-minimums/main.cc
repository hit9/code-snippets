// https://leetcode.cn/problems/sum-of-subarray-minimums
// 907. 子数组的最小值之和
// 给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr
// 的每个（连续）子数组。 由于答案可能很大，因此 返回答案模 10^9 + 7 。
//
// 输入：arr = [3,1,2,4] 输出：17 解释： 子数组为
// [3]，[1]，[2]，[4]，[3,1]，[1,2]，[2,4]，[3,1,2]，[1,2,4]，[3,1,2,4]。
// 最小值为 3，1，2，4，1，1，2，1，1，1，和为 17。

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// 一个很好的例子是: 11,9,81,84,43,90,3,8

using ll = unsigned long long;
class Solution {
   public:
    int sumSubarrayMins(vector<int>& arr) {
        int mod = 1000000007;
        int n = arr.size();
        ll ans = 0;
        stack<int> s;  // 栈中是下标，单调递增栈

        auto reduce = [&](int i) {
            // 当前要 pop 的元素
            int j = s.top();
            s.pop();

            // j 这个元素重复的宽度 w 和积累的层数 h
            int w = (i - j);
            int h = s.empty() ? (j + 1) : (j - s.top());

            // 加上这个元素积累的总和
            ans += (ll)(w * h) * (ll)arr[j];
        };

        for (int i = 0; i < n; i++) {
            while (!s.empty() && arr[s.top()] >= arr[i]) reduce(i);
            s.push(i);
        }
        while (!s.empty()) reduce(n);
        return ans % mod;
    }
};

int main(void) {
    Solution s;
    vector<int> arr{11, 81, 94, 43, 3};
    cout << s.sumSubarrayMins(arr) << endl;
    return 0;
}
