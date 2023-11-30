#include <vector>
using namespace std;
using ll = long long;
class Solution {
   public:
    // 计算乘积 <= x 的个数
    // 输入的 x 越大，个数应该越多
    ll count(const vector<int>& nums1, const vector<int>& nums2, ll x) {
        if (nums1.size() > nums2.size()) return count(nums2, nums1, x);

        ll c = 0;
        // ab <= x
        for (ll a : nums1) {
            if (a == 0 && x >= 0)
                // 如果 a == 0, 直接判断 x 是否非负, 所有都可以
                c += nums2.size();
            else if (a > 0) {
                // 如果 a > 0, 相当于求 b <= x/a 的右界
                // 对找到的 l 的左侧计数，越小的才是答案
                ll l = 0, r = nums2.size() - 1;
                while (l < r) {
                    ll m = (l + r + 1) >> 1;
                    if (nums2[m] * a <= x)
                        l = m;
                    else
                        r = m - 1;
                }
                // 注意 check
                if (nums2[l] * a <= x) c += l + 1;
            } else if (a < 0) {
                // 如果 a < 0, 相当于求 b >= x/a 的左界
                // 对找到的 l 的右侧计数，越大的才是答案
                ll l = 0, r = nums2.size() - 1;
                while (l < r) {
                    ll m = (l + r) >> 1;
                    if (nums2[m] * a <= x)
                        r = m;
                    else
                        l = m + 1;
                }
                // 注意 check
                if (nums2[l] * a <= x) c += nums2.size() - l;
            }
        }
        return c;
    }

    ll kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, ll k) {
        // 最大最小一定在第一项和最后一项的四个里面产生.
        vector<ll> p{
            (ll)nums1[0] * (ll)nums2[0],
            (ll)nums1[0] * (ll)nums2[nums2.size() - 1],
            (ll)nums1[nums1.size() - 1] * (ll)nums2[0],
            (ll)nums1[nums1.size() - 1] * (ll)nums2[nums2.size() - 1],
        };

        // 二分答案
        ll l = *min_element(p.begin(), p.end());
        ll r = *max_element(p.begin(), p.end());

        while (l < r) {
            ll m = (l + r) >> 1;
            if (count(nums1, nums2, m) >= k)
                r = m;
            else
                l = m + 1;
        }
        return l;
    }
};
