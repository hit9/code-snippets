#include <vector>

using namespace std;

// https://www.quickperm.org/
class Solution {
   public:
    vector<vector<int>> permute(vector<int>& a) {
        vector<vector<int>> ans{a};
        int n = a.size();
        int p[n + 1];
        memset(p, 0, sizeof p);
        int i = 1;
        while (i < n) {
            if (p[i] < i) {
                int j = (i & 1) * p[i];
                std::swap(a[i], a[j]);
                ans.push_back(a);
                p[i]++;
                i = 1;
            } else {
                p[i] = 0;
                i++;
            }
        }
        return ans;
    }
};
