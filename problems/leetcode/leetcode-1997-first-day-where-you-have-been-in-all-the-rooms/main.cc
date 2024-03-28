#include <vector>
using namespace std;
class Solution {
   public:
    // 注意关键条件: 奇数时,只能向前跳
    // 所以第一次到达 i 的话,只能从左边i-1而来,而且左边 [0..i] 上都是偶数状态
    // 定义第一次到达 i 的步数是 f[i]
    // 到达 i 有 4 步:
    // 1. 第一次到达 i-1, 共 f[i-1] 步, 此时 i-1 是奇数次, 此时 [0..i-1]
    // 上都是偶数
    // 2. 回退到 j=nextVisit[i-1], 消耗1步
    // 3. 从 j 回到 i-1, 消费 f[i-1] - f[j], 第二次到达 i-1, 其状态是偶数次
    // 4. 从 i-1 到 i , 消耗 1步
    // 所以 f[i] = f[i-1] + f[i-1] - f[nextVisit[i-1]] + 2
    // 注意大数和 mod 的细节
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        int n = nextVisit.size();
        long long mod = 1e9 + 7;
        // f[x] 记录第 x 个房间的访问次数
        vector<long long> f(n, 0);
        f[0] = 0;

        for (int i = 1; i < n; i++) {
            int j = nextVisit[i - 1];
            f[i] = (2 + f[i - 1] + f[i - 1] - f[j]) % mod;
            // f[i] 可能为负数..
            if (f[i] < 0) f[i] += mod;
        }
        return f[n - 1];
    }
};
