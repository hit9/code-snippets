#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        // m 记录前缀和的次数
        unordered_map<int, int> m;

        int ans = 0;
        int sum = 0;
        m[sum] = 1;

        for (int i = 0; i < n; i++) {
            sum += nums[i];
            int j = sum - k;
            ans += m[j];
            m[sum]++;
        }
        return ans;
    }
};
