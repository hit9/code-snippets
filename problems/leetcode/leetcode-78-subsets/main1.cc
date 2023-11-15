#include <vector>
using namespace std;
class Solution {
   public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> d{{}};
        for (int i = 0; i < nums.size(); i++) {
            int n = d.size();
            for (int j = 0; j < n; j++) {
                vector<int> a(d[j]);
                a.push_back(nums[i]);
                d.push_back(a);
            }
        }
        return d;
    }
};

