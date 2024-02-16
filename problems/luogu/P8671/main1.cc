#include <cstdio>
using namespace std;
int josephus(int n, int k) {
    if (n == 1) return 0;
    if (k == 1) return n - 1;
    if (k > n) return (josephus(n - 1, k) + k) % n;
    int f = josephus(n - n / k, k);
    f -= n % k;
    f += f < 0 ? n : (f / (k - 1));
    return f;
}

int main(void) {
    int n, k;
    scanf("%d%d", &n, &k);
    printf("%d\n", josephus(n, k) + 1);
    return 0;
}
