#include <vector>

using namespace std;
class Solution {
   public:
    void dfs(vector<int>& a, vector<int>& path, vector<vector<int>>& ans,
             int target, int start) {
        if (target < 0) return;
        if (target == 0) ans.push_back(path);
        for (int i = start; i < a.size(); i++) {
            if (a[i] > target) continue;  // 此剪枝提速显著, beats 100%
            path.push_back(a[i]);
            dfs(a, path, ans, target - a[i], i);
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> path;
        dfs(candidates, path, ans, target, 0);
        return ans;
    }
};
