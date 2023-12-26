#include <deque>
#include <vector>
using namespace std;
class Solution {
   public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size();
        int f[n];
        deque<int> q;  // 存储下标, 按 f 单降
        q.push_back(0);

        // f[i] 表示以 a[i] 结尾时的序列的最大和
        f[0] = nums[0];
        int ans = f[0];  // 要求非空序列，所以最开始必须选 a[0]

        for (int i = 1; i < n; i++) {
            // 维护队头合法性
            while (!q.empty() && q.front() + k < i) q.pop_front();

            // 不基于前面的, 只选择 a[i]
            f[i] = nums[i];
            // 基于前面的, 选择 f[j] + a[i], 队头为最优决策点
            if (!q.empty()) f[i] = max(f[i], f[q.front()] + nums[i]);

            ans = max(ans, f[i]);

            // 维护单调递减性质
            while (!q.empty() && f[q.back()] < f[i]) q.pop_back();
            q.push_back(i);
        }
        return ans;
    }
};
