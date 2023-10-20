#include <vector>
using namespace std;
class Solution {
   public:
    long long mostPoints(vector<vector<int>>& questions) {
        vector<long long> scores(questions.size(), 0);
        long long ans = 0;
        for (auto i = 0; i < questions.size(); i++) {
            scores[i] += questions[i][0];
        }
    }
};
