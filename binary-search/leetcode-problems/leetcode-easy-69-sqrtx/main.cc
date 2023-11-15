class Solution {
   public:
    int mySqrt(int x) {
        int l = 0, r = x;
        while (l < r) {
            auto m = ((long)l + (long)r + 1) >> 1;
            if (m > x / m)
                r = m - 1;
            else
                l = m;
        }
        return l;
    }
};
