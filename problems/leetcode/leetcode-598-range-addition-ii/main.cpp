#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        vector<int> overlap;
        overlap.push_back(m), overlap.push_back(n);

        for (const auto& op : ops) {
            overlap[0] = min(overlap[0], op[0]);
            overlap[1] = min(overlap[1], op[1]);
        }

        return overlap[0] * overlap[1];
    }
};
