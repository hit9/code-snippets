#include <vector>
using namespace std;
class Solution {
   public:
    vector<int> chosen;
    vector<vector<int>> ans;
    void dfs(vector<int>& a, int k) {
        if (k == a.size()) {
            ans.push_back(chosen);
            return;
        }

        chosen.push_back(a[k]);  // 选 a[k]
        dfs(a, k + 1);           // 继续问题 dfs(k+1..N)
        chosen.pop_back();       // 撤销

        dfs(a, k + 1);           // 不选 a[k], 继续问题 dfs(k+1..N)
    }

    vector<vector<int>> subsets(vector<int>& a) {
        dfs(a, 0);
        return ans;
    }
};
