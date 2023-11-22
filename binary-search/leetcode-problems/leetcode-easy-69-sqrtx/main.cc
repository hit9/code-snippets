class Solution {
   public:
    int mySqrt(int x) {
        // 要找 m^2 <= x 的右界
        // 等价于找 m - x/m <= 0 的右界
        auto f = [&](int m) { return m - x / m; };
        int l = 0, r = x;
        while (l < r) {
            auto m = ((long)l + (long)r + 1) >> 1;
            if (f(m) <= 0)
                l = m;
            else
                r = m - 1;
        }
        return l;
    }
};
