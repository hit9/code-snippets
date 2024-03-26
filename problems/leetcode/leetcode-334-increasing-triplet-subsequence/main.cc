#include <vector>
using namespace std;
class Solution {
   public:
    bool increasingTriplet(vector<int>& nums) {
        // b 是长度为 2 的严格递增的末尾元素的最小值
        // c 是长度为 1 的严格递增的末尾元素的最小值, 也就是历史最小值
        int b = INT_MAX, c = INT_MAX;
        for (auto x : nums) {
            if (x > b)
                return true;
            else if (x > c) {  // x <= b && x > c
                b = x;
            } else {  // x <= c
                c = x;
            }
        }
        return false;
    }
};
