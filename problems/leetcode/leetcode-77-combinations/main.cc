#include <vector>
using namespace std;
class Solution {
   public:
    void dfs(vector<vector<int>>& ans, vector<int>& path, int n, int k,
             int start) {
        if (path.size() > k) return;
        if (path.size() == k) ans.push_back(path);
        for (int i = start; i <= n; i++) {
            path.push_back(i);
            dfs(ans, path, n, k, i + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> path;
        dfs(ans, path, n, k, 1);
        return ans;
    }
};
