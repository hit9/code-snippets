#include <algorithm>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    int maxConsecutive(int bottom, int top, vector<int>& special) {
        set<int> s{bottom - 1, top + 1};

        unordered_map<int, int> d;
        d[top - bottom + 1] = 1;

        for (auto x : special) {
            auto [it, _] = s.insert(x);
            int n = *next(it);
            int p = *prev(it);
            int a = n - x - 1;
            int b = x - p - 1;

            ++d[a], ++d[b];
            --d[a + b + 1];
        }

        int ans = 0;
        for (auto [k, v] : d) {
            if (v > 0) ans = max(ans, k);
        }
        return ans;
    }
};
