#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    int longestConsecutive(vector<int>& nums) {
        // L(x) 表示以 x 为右端点的连续序列的最大长度
        // R(x) 表示以 x 为左端点的连续序列的最大长度
        unordered_map<int, int> L, R;

        int ans = 0;

        for (auto x : nums) {
            if (L[x] || R[x]) continue;

            // 更新 x 为端点的序列长度
            int l = L[x - 1], r = R[x + 1];
            L[x] = l + 1, R[x] = r + 1;

            int d = l + r + 1;

            // 路过 x 的最长连续序列的长度
            ans = max(ans, d);

            // 两端需要维护, 会影响后续迭代的计算
            // 中间已经连续的都无需维护, 因为不会再被利用, 对后续没有影响
            L[x + r] = R[x - l] = d;
        }

        return ans;
    }
};
