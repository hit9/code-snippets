#include <vector>
using namespace std;
class Solution {
   public:
    // 目标左边的值均 >= nums[0]
    // 二分枚举答案，找到满足 num >= nums[0] 这个表达式的右界 l
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;  // 可行解不包括 n
        while (l < r) {
            int m = (l + r + 1) >> 1;
            if (nums[m] < nums[0])  // 不满足 num >= nums[0] 时, 右侧缩小
                r = m - 1;
            else
                l = m;
        }
        // 注意防止 l+1 = n 的情况
        return nums[(l + 1) % nums.size()];
    }
};
