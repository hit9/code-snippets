#include <vector>
using namespace std;
class Solution {
   public:
    int minimumLevels(vector<int>& possible) {
        // 预处理 possible
        for (auto& x : possible)
            if (x == 0) x = -1;
        // 前缀和  sum[..i] 表示 possible[..i] 的和
        int n = possible.size();
        vector<int> sum(n, 0);
        sum[0] = possible[0];
        for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + possible[i];
        // 从前缀和数组中自左向右找到 2*sum[i] > sum[n-1] 的位置
        int j = 0;
        while (j < n && 2 * sum[j] <= sum[n - 1]) j++;
        if (j >= n) return -1;
        if (j == n - 1) return -1;  // bob 至少要走一次
        return j + 1;
    }
};
