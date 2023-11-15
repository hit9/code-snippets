// https://leetcode.cn/problems/wiggle-subsequence

#include <vector>

using namespace std;

class Solution {
   public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() == 1) return 1;

        int k = 1;

        // 1 up, -1 down, 0: undetermined
        int direction = 0;

        for (int i = 1; i < nums.size(); i++) {
            if (direction == 0) {
                if (nums[i] > nums[i - 1]) {
                    direction = 1;
                    k++;
                } else if (nums[i] < nums[i - 1]) {
                    direction = -1;
                    k++;
                }
            } else if (direction == 1) {
                if (nums[i] < nums[i - 1]) {
                    direction = -1;
                    k++;
                }
            } else {
                if (nums[i] > nums[i - 1]) {
                    direction = 1;
                    k++;
                }
            }
        }
        return k;
    }
};
