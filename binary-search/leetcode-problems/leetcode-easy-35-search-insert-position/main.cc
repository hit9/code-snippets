#include <vector>
using namespace std;
class Solution {
   public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0, r = nums.size();
        while (l < r) {
            int m = (l + r) >> 1;
            if (nums[m] < target)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }
};
