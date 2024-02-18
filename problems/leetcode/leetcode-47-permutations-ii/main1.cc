#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

// set 去重

class Solution {
   public:
    void dfs(vector<int>& nums, int start, vector<vector<int>>& ans) {
        if (start >= nums.size() - 1) {
            ans.push_back(nums);
            return;
        }
        unordered_set<int> s;

        for (int i = start; i < nums.size(); i++) {
            if (s.find(nums[i]) != s.end()) continue;
            s.insert(nums[i]);
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
