#include <algorithm>
#include <vector>
using namespace std;

// 思路：因为只能增加，先将数组排序。
// 问题转化为对于每一个下标 R, 选取一段区间 [L,R] 使得区间和增加至多
// k，求最长的区间长度。
// 每一步+1的操作，其实就是算区间和的增加量，把每一个数变更到右端 L 的值
using ll = long long;
class Solution {
   public:
    int maxFrequency(vector<int>& a, int k) {
        ll s = 0;  // 窗口内实际区间和
        int ans = 0;
        sort(a.begin(), a.end());
        for (int L = 0, R = 0; R < a.size(); R++) {
            s += a[R];
            // 变更后区间和至多是 (R-L+1)*a[R]
            while (L < R && (ll)a[R] * (R - L + 1) > k + s) {
                s -= a[L++];
            }
            ans = max(ans, R - L + 1);
        }
        return ans;
    }
};
