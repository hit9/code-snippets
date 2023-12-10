
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

using P = pair<int, int>;  // value, index
auto cmp_value(const P& x, const P& y) { return x.first < y.first; }
auto cmp_index(const P& x, const P& y) { return x.second < y.second; }

class Solution {
   public:
    // [start, end]
    void cdq(vector<int>& dp, vector<P>& a, int start, int end) {
        if (end <= start) return;

        int mid = (start + end) >> 1;

        // 分治左边 [start, mid]
        cdq(dp, a, start, mid);

        // 左右分别按值有序, 然后计算左边对右边的贡献
        sort(a.begin() + start, a.begin() + mid + 1, cmp_value);
        sort(a.begin() + mid + 1, a.begin() + end + 1, cmp_value);

        // 对右边的每个 j, 找到左边值比它小的 i 的最大的 dp 值
        // 因为已经按值有序，所以 i 不必回溯，此部分的总时间复杂度是 n
        int i = mid + 1;
        int ma = 0, j = start;
        while (i <= end) {
            while (j <= mid && a[j].first < a[i].first) {
                ma = std::max(ma, dp[a[j++].second]);
            }
            dp[a[i].second] = std::max(dp[a[i].second], ma + 1);
            i++;
        }

        // 恢复秩序
        sort(a.begin() + mid + 1, a.begin() + end + 1, cmp_index);

        // 分治右边 [mid+1, end]
        cdq(dp, a, mid + 1, end);
    }
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<P> a(n);
        for (int i = 0; i < n; i++) a[i] = {nums[i], i};
        vector<int> dp(n, 1);
        cdq(dp, a, 0, n - 1);
        return *max_element(dp.begin(), dp.end());
    }
};

int main(void) {
    Solution s;
    vector<int> nums{
        -813, 82,   -728, -82,  -432, 887,  -551, 324,  -315, 306,  -164, -499,
        -873, -613, 932,  177,  61,   52,   1000, -710, 372,  -306, -584, -332,
        -500, 407,  399,  -648, 290,  -866, 222,  562,  993,  -338, -590, 303,
        -16,  -134, 226,  -648, 909,  582,  177,  899,  -343, 55,   629,  248,
        333,  1,    -921, 143,  629,  981,  -435, 681,  844,  349,  613,  457,
        797,  695,  485,  15,   710,  -450, -775, 961,  -445, -905, 466,  942,
        995,  -289, -397, 434,  -14,  34,   -903, 314,  862,  -441, 507,  -966,
        525,  624,  -706, 39,   152,  536,  874,  -364, 747,  -35,  446,  -608,
        -554, -411, 987,  -354, -700, -34,  395,  -977, 544,  -330, 596,  335,
        -612, 28,   586,  228,  -664, -841, -999, -100, -620, 718,  489,  346,
        450,  772,  941,  952,  -560, 58,   999,  -879, 396,  -101, 897,  -1000,
        -566, -296, -555, 938,  941,  475,  -260, -52,  193,  379,  866,  226,
        -611, -177, 507,  910,  -594, -856, 156,  71,   -946, -660, -716, -295,
        -927, 148,  620,  201,  706,  570,  -659, 174,  637,  -293, 736,  -735,
        377,  -687, -962, 768,  430,  576,  160,  577,  -329, 175,  51,   699,
        -113, 950,  -364, 383,  5,    748,  -250, -644, -576, -227, 603,  832,
        -483, -237, 235,  893,  -336, 452,  -526, 372,  -418, 356,  325,  -180,
        134,  -698};
    cout << s.lengthOfLIS(nums) << endl;
    return 0;
}
