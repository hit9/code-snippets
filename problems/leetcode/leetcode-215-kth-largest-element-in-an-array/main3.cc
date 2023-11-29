#include <algorithm>
#include <vector>
using namespace std;

// 二分判定

class Solution {
   public:
    // 计算>=x 的元素数目, 降序函数
    int count(const vector<int>& nums, int x) {
        int c = 0;
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] >= x) c++;
        return c;
    }
    int findKthLargest(vector<int>& nums, int k) {
        int l = *min_element(nums.begin(), nums.end());
        int r = *max_element(nums.begin(), nums.end());

        // 找 >=x 的元素个数不超过 k 的 x 的最大的 x
        // 也就是找满足 count(x) >= k 的 x 的右界
        while (l < r) {
            int m = (l + r + 1) >> 1;
            if (count(nums, m) < k)
                // count 是降序, 说明 m 大了
                // 所以右侧排除, 收缩到 m-1
                // 防止死循环，所以每次取 m = (l+r+1)>>1
                r = m - 1;
            else
                l = m;
        }
        return l;
    }
};
