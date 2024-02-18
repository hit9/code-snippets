#include <algorithm>
#include <vector>
using namespace std;
class Solution {
   public:
    void dfs(vector<int>& a, int start, vector<int>& path,
             vector<vector<int>>& ans) {
        ans.push_back(path);
        for (int i = start; i < a.size(); i++) {
            if (i > start && a[i] == a[i - 1]) continue;
            path.push_back(a[i]);
            dfs(a, i + 1, path, ans);
            path.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& a) {
        sort(a.begin(), a.end());
        vector<vector<int>> ans;
        vector<int> path;
        dfs(a, 0, path, ans);
        return ans;
    }
};
