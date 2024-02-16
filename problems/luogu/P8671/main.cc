#include <cstdio>
using namespace std;
int main(void) {
int n, k;
    scanf("%d%d", &n, &k);
    int f = 0;
    for (int i = 2; i <= n; i++) {
        f = (f + k) % i;
    }
    printf("%d\n", f + 1);
    return 0;
}
