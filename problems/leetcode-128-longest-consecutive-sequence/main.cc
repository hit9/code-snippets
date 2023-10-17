#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    int longestConsecutive(vector<int>& nums) {
        // 开始填表 x
        // D[x] 是 x 作为一个端点时，最长的连续区间的长度
        unordered_map<int, int> D;

        // 先全部初始化为 0
        for (auto x : nums) D[x] = 0;

        // m 跟踪最大的 d;
        int m = 0;

        for (auto x : nums) {
            // 填表过程:
            // 为什么要更新两端:
            //
            if (D[x] == 0) {
                int L = D[x - 1];  // 左侧 x-1 为右端点的情况
                int R = D[x + 1];  // 右侧 x+1 为左断点的情况
                int d = 1 + L + R;
                D[x - L] =
                    d;  // 左侧的 x-L 处为左端点的情况，长度要扩大到 1+L+R;
                D[x + R] = d;  // 右侧的 x+R 处同理
                               // x 处作为端点的情况，应该取 L+1 和 R+1 的最大值
                               // (算上自己一个元素)
                D[x] = std::max(L + 1, R + 1);
                if (d > m) m = d;
            }
        }

        return m;
    }
};

int main(void) {
    Solution solution;
    vector<int> nums{0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << solution.longestConsecutive(nums) << endl;
    return 0;
}
