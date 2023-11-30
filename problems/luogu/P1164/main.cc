#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int kp01(int n, int m, const vector<int>& v) {
    // f[j] 表示当前花费 j 元的时候，总共可以多少种方案
    int f[m + 1];
    memset(f, 0, sizeof f);

    // 最开始，不花费任何钱，也算做一种方案，方便递推
    f[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = m; j >= v[i]; j--) {
            f[j] += f[j - v[i]];
        }
    }
    return f[m];
}

int main(void) {
    int n, m;
    cin >> n;
    cin >> m;
    getchar();
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    getchar();
    cout << kp01(n, m, v) << endl;
    return 0;
}
