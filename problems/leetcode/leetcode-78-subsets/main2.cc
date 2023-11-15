// 回溯递归思路
#include <vector>
using namespace std;
class Solution {
   public:
    void dfs(vector<vector<int>>& ans, vector<int>& path, vector<int>& nums,
             int start) {
        ans.push_back(path);
        for (int i = start; i < nums.size(); i++) {
            path.push_back(nums[i]);  // 选择当前元素，进一步更深的递归
            dfs(ans, path, nums, i + 1);
            path.pop_back();  // 撤销选择，从下一个起点开始选择
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> path;
        dfs(ans, path, nums, 0);
        return ans;
    }
};
