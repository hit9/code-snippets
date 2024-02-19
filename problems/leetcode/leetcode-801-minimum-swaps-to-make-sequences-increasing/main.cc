#include <vector>
using namespace std;
class Solution {
   public:
    int minSwap(vector<int>& a, vector<int>& b) {
        int f[2] = {0, 1};  // f[0] 表示不交换 i, f[1] 表示交换 i 的最小次数
        for (int i = 1; i < a.size(); i++) {
            // 注意先放大, 以便取到正确的 min
            int f0 = f[0], f1 = f[1];
            memset(f, 0x3f, sizeof f);

            int a1 = a[i - 1], a2 = a[i], b1 = b[i - 1], b2 = b[i];
            if (a1 < a2 && b1 < b2) {
                // 都不交换, f[0] 不变
                f[0] = f0;
                // 都交换, 也就是基于上一次的交换下, 继续交换一次, f[1] 增加
                f[1] = f1 + 1;
            }
            if (a1 < b2 && b1 < a2) {
                // 注意和前面的取最小
                // 只可以交换一对
                // 也就是基于上一次不交换,进行交换一次
                f[1] = min(f[1], f0 + 1);
                // 或者基于上一次交换,这一次不交换
                f[0] = min(f[0], f1);
            }
        }
        return min(f[0], f[1]);
    }
};
