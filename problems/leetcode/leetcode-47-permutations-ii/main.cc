#include <algorithm>
#include <vector>
using namespace std;

// 排序去重

class Solution {
   public:
    void dfs(vector<int>& nums, int start, vector<vector<int>>& ans) {
        if (start >= nums.size() - 1) {
            ans.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); i++) {
            sort(nums.begin() + start, nums.end());
            if (i > start && nums[i] == nums[i - 1]) continue;
            std::swap(nums[i], nums[start]);
            dfs(nums, start + 1, ans);
            std::swap(nums[i], nums[start]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        dfs(nums, 0, ans);
        return ans;
    }
};
