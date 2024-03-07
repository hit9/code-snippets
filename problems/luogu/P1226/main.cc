#include <cstdio>

int fastpowermod(int a, int b, int p) {
    int factor = a;
    int result = 1;
    int remain = b;
    while (remain > 0) {
        if (remain & 1) {
            // 奇数
            result = (long long)result * factor % p;
            remain--;
        } else {
            // 偶数
            remain >>= 1;                             // 剩余指数拆半
            factor = (long long)factor * factor % p;  // 因子自乘翻倍
        }
    }
    return result % p;
}

int main(void) {
    int a, b, p;
    scanf("%d%d%d", &a, &b, &p);
    int c = fastpowermod(a, b, p);
    printf("%d^%d mod %d=%d", a, b, p, c);
    return 0;
}
