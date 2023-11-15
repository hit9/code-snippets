#include <vector>
using namespace std;

class Solution {
   public:
    // 整个数组一定是奇数, 肯定一边多一边少
    // m 一直是正中间的元素, L 和 R 长度必相等
    // [    L   ] [m]  [   R   ]
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        int l = 0;
        int r = n - 1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (m >= 1 && nums[m - 1] == nums[m]) {
                // 和左边的元素相等，
                // 除去这两个左边有 (m-1-l) 个
                // 如果它是偶数，则向右, 比如
                //  [3,3,7,7,8,9,9]
                //         m
                // 否则向左, 比如
                //  [1,1,2,3,3,4,4,8,8]
                //           m
                if ((m - 1 - l) & 1)
                    r = m - 2;
                else
                    l = m + 1;
            } else if (m <= n - 2 && nums[m + 1] == nums[m]) {
                // 同理分析
                if ((r - (m + 1)) & 1)
                    l = m + 2;
                else
                    r = m - 1;
            } else {
                // 和任何一个邻居都不相等, 哪怕是边界
                return nums[m];
            }
        }
        return 0;  // 不可到达
    }
};
