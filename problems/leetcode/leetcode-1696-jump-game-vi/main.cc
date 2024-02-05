#include <deque>
#include <vector>
using namespace std;
class Solution {
   public:
    int maxResult(vector<int>& a, int k) {
        int n = a.size();
        int f[n];      // 跳到 i 处的最高分数是 f[i]
        deque<int> q;  // 按分数递减, 存储下标
        for (int i = 0; i < n; i++) {
            // 维护队头
            while (!q.empty() && q.front() + k < i) q.pop_front();
            // 计算得分
            f[i] = (q.empty() ? 0 : f[q.front()]) + a[i];
            // 维护队尾
            while (!q.empty() && f[q.back()] < f[i]) q.pop_back();
            q.push_back(i);
        }
        return f[n - 1];
    }
};
