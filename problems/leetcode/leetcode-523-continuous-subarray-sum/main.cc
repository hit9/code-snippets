#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
    using ull = unsigned long long;

   public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> d;
        ull sum = 0;
        d.insert({0, -1});

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            int x = sum % k;
            if (d.find(x) != d.end()) {
                if (d[x] + 1 < i) return true;
            }
            d.insert({x, i});
        }

        return false;
    }
};
