
#include <vector>
using namespace std;
// 对向双指针
class Solution {
   public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        int L = 0, R = n - 1;
        vector<int> ans;
        while (L <= R) {
            if (abs(nums[L]) > abs(nums[R])) {
                ans.push_back(nums[L] * nums[L]);
                L++;
            } else {
                ans.push_back(nums[R] * nums[R]);
                R--;
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
