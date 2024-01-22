#include <stack>
#include <vector>
using namespace std;
class Solution {
   public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n = heights.size();
        vector<int> ans(n, 0);
        stack<int> s;
        for (int i = 0; i < n; i++) {
            while (!s.empty() && heights[s.top()] < heights[i]) {
                // 可以看到 heights[i]
                ans[s.top()]++;
                s.pop();
            }
            if (!s.empty())ans[s.top()]++;
            s.push(i);
        }
        return ans;
    }
};
