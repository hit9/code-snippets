class Solution {
   public:
    double f(double x, long long n) {
        if (n < 0) return 1.0 / f(x, 0L - n);
        double a = x;
        double b = 1;
        while (n) {
            if (n & 1) {
                b *= a;
                n--;
            } else {
                n >>= 1;
                a *= a;
            }
        }
        return b;
    }
    double myPow(double x, int n) {
        return f(x, n);
    }
};
