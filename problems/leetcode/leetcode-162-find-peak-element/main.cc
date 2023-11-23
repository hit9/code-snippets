#include <vector>
using namespace std;
class Solution {
   public:
    int findPeakElement(vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (m < nums.size() - 1 && nums[m] < nums[m + 1])
                // 排除左边, 右侧必有峰
                l = m + 1;
            else
                r = m;
        }
        return l;
    }
};
