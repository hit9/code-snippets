#include <algorithm>
#include <vector>
using namespace std;

class Solution {
   public:
    void dfs(vector<int>& a, vector<int>& path, vector<bool>& visited,
             vector<vector<int>>& ans) {
        if (path.size() == a.size()) {
            ans.push_back(path);
            return;
        }

        for (int i = 0; i < a.size(); i++) {
            if (visited[i]) continue;
            if (i > 0 && visited[i-1] && a[i - 1] == a[i]) continue;
            visited[i] = true;
            path.push_back(a[i]);
            dfs(a, path, visited, ans);
            path.pop_back();
            visited[i] = false;
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& a) {
        sort(a.begin(), a.end());
        vector<vector<int>> ans;
        vector<int> path;
        vector<bool> visited(a.size(), false);
        dfs(a, path, visited, ans);
        return ans;
    }
};
