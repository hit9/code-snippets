#include <cstdio>
using namespace std;

using ll = unsigned long long;

// q will always < nk
int josephus(int n, int k, ll q) {
    if (k == 1) return n - 1;
    for (q = q * k + k - 1; q >= n; q = q - n + (q - n) / (k - 1))
        ;
    return q;
}

int main(void) {
    int n, k;
    scanf("%d%d", &n, &k);
    printf("%d\n", josephus(n, k, n - 1) + 1);
    return 0;
}
