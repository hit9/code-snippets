
#include <cstring>
#include <iostream>

using namespace std;

using ull = unsigned long long;
const ull mod = 2147483648;

int solve(int n) {
    ull f[n + 1];
    memset(f, 0, sizeof f);

    f[0] = 1;

    for (int i = 1; i < n; i++) {
        for (int j = i; j <= n; j++) {
            f[j] += f[j - i] % mod;
        }
    }
    return f[n] % mod;
}

int main(void) {
    int n;
    cin >> n;
    getchar();
    cout << solve(n) << endl;
    return 0;
}
