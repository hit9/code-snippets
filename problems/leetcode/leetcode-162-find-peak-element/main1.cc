
#include <vector>
using namespace std;
class Solution {
   public:
    int findPeakElement(vector<int>& nums) {
        auto check = [&](int i) {
            if (i < nums.size() - 1 && nums[i] < nums[i + 1]) return false;
            return true;
        };

        int l = 0;
        int r = nums.size() - 1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (check(m))
                r = m;
            else
                l = m - 1;
        }
        return l;
    }
};
