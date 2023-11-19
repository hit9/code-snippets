// 树状数组的思路

#include <vector>

using namespace std;

class BIT {
   private:
    int n;
    vector<int> c;

   public:
    explicit BIT(int n) : n(n), c(vector<int>(n, 0)) {}
    int ask(int x) {
        int ans = 0;
        for (; x; x -= x & -x) ans += c[x];
        return ans;
    }
    void add(int x, int v) {
        for (; x <= n; x += x & -x) c[x] += v;
    }
};

class Solution {
   public:
    int reversePairs(vector<int>& a) {
        int n = a.size();
        if (n == 0) return 0;

        // 离散化: 拷贝后，排序+去重
        vector<int> r(a.begin(), a.end());
        sort(r.begin(), r.end());

        int m = 0;  // m 以左不包含重复元素

        // 去重
        for (int i = 0; i < n; i++)
            if (i == 0 || r[i] != r[i - 1]) r[m++] = r[i];

        // 用离散化后的数据重写a
        for (int i = 0; i < n; i++) {
            auto low = lower_bound(r.begin(), r.begin() + m, a[i]);
            a[i] = low - r.begin() + 1;  // 1~m;
        }

        // 树状数组优化
        BIT b(500001);

        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            auto x = a[i];
            ans += b.ask(x - 1);
            b.add(x, 1);
        }
        return ans;
    }
};
