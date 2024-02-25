class Solution {
   public:
    int findComplement(int n) {
        int x = n;
        while (1) {
            int p = x & -x;
            if (p == x) break;
            x -= p;
        }
        int q = 1;
        while (0 == (x & 1)) {
            q <<= 1;
            q |= 1;
            x >>= 1;
        }
        return q ^ n;
    }
};
