#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// 问题转化为:
// 对于一个 x ，如果满足分割后各个数组的和都 <= x 的最小分割数不多于 k
// 找这种最小的这种 x

class Solution {
   public:
    // 给定的 x, 返回分割后各个数组的和都 <= x 所需的最小分割数 k
    // 对于一个确定的数组而言，输入的 x 越大，返回的 k 越小，所以注意是反向单调
    // 输入的 x 要保证至少为 max(nums)
    int count(const vector<int>& nums, int x) {
        int c = 1;
        int sum = 0;
        for (auto num : nums) {
            if (sum + num > x) {
                sum = 0;
                c++;
            }
            sum += num;
        }
        return c;
    }

    // 二分判定找 满足  count(x) <= k 的左界
    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        int r = accumulate(nums.begin(), nums.end(), 0);
        int l = *max_element(nums.begin(), nums.end());

        // 注意  count 是降序的, 做一个 check 函数来转换为升序
        auto check = [&](const vector<int>& nums, int x) {
            return n - count(nums, x);
        };

        // 二分枚举找满足 check(x) >= n - k 的 x 的左界

        while (l < r) {
            int m = (l + r) >> 1;
            if (check(nums, m) >= n - k)
                r = m;
            else
                l = m + 1;
        }

        return l;
    }
};

int main(void) {
    Solution s;
    vector<int> nums{1, 4, 4};
    cout << s.count(nums, 1) << endl;
    cout << s.splitArray(nums, 3) << endl;
    return 0;
}
