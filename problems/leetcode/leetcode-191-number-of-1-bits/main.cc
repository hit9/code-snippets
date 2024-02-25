#include <cstdint>
using namespace std;
class Solution {
   public:
    int hammingWeight(uint32_t x) {
        int ans = 0;
        while (x) {
            x -= x & -x;
            ans ++;
        }
        return ans;
    }
};
