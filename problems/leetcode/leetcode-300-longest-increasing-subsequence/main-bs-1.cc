// 最长递增子序列问题
// 求长度

#include<vector>
#include<algorithm>
using namespace std;
class Solution {
   public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> p{nums[0]};

        for (int i = 1; i < nums.size(); i++) {
            if (auto num = nums[i]; num > p.back())
                p.push_back(num);
            else {
                auto j = lower_bound(p.begin(),p.end(), num);
                *j = num;
            }
        }
        return p.size();
    }
};
