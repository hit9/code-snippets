class Solution {
   public:
    bool isPowerOfTwo(int n) {
        if (!n) return false;
        if (n < -0x7ffffff) return false;
        return (n & (-n)) == n;
    }
};
