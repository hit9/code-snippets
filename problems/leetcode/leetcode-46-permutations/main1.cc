#include <vector>

using namespace std;

class Solution {
   public:
    void dfs(vector<int>& nums, vector<int>& path, vector<bool>& visited,
             vector<vector<int>>& ans) {
        if (path.size() == nums.size()) {
            ans.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (visited[i]) continue;
            visited[i] = true;
            path.push_back(nums[i]);
            dfs(nums, path, visited, ans);
            path.pop_back();
            visited[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> path;
        vector<bool> visited(nums.size(), false);
        dfs(nums, path, visited, ans);
        return ans;
    }
};
