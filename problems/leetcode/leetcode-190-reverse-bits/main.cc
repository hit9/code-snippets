#include <cstdint>
class Solution {
   public:
    uint32_t reverseBits(uint32_t n) {
        int k = 32, ans = 0;
        while (k--) {
            ans <<= 1;
            ans += n & 1;
            n >>= 1;
        }
        return ans;
    }
};
