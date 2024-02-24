#include <vector>

using namespace std;

class Solution {
   public:
    int countPrimes(int n) {
        if (n <= 2) return 0;
        vector<int> table(n, 0);  // 0 是素数, 未被标记
        table[0] = 1;
        table[1] = 1;

        for (int i = 2; i * i < n; i++) {
            if (table[i]) continue;
            // 标记 i 的所有倍数, 只需要从 i*i 开始标记
            for (int j = i * i; j < n; j += i) {
                table[j] = 1;  // 标记
            }
        }

        // 计数
        int ans = 0;
        for (int i = 0; i < n; i++)
            if (!table[i]) ans++;
        return ans;
    }
};
