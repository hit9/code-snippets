class Solution {
   public:
    bool isPerfectSquare(int num) {
        int l = 0, r = num;
        while (l < r) {
            int m = ((long)l + (long)r + 1) >> 1;
            if (m > num / m)
                r = m - 1;
            else
                l = m;
        }
        return (long)l * l == (long)num;
    }
};
