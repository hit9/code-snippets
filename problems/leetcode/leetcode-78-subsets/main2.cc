// 回溯递归思路
#include <vector>
using namespace std;
class Solution {
   public:
    void dfs(vector<vector<int>>& ans, vector<int>& path, vector<int>& a,
             int start) {
        ans.push_back(path);
        for (int i = start; i < a.size(); i++) {
            path.push_back(a[i]);  // 选择当前元素，进一步更深的递归
            dfs(ans, path, a, i + 1);
            path.pop_back();  // 撤销选择，从下一个起点开始选择
        }
    }

    vector<vector<int>> subsets(vector<int>& a) {
        vector<vector<int>> ans;
        vector<int> path;
        dfs(ans, path, a, 0);
        return ans;
    }
};
