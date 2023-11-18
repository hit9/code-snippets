#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    int n;
    cin >> n;
    getchar();

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    getchar();

    // sum 是以当前元素结尾的最大连续数组的和
    int sum = a[0];
    int ans = sum;

    for (int i = 1; i < n; i++) {
        if (sum < 0) sum = 0;
        sum += a[i];
        ans = std::max(ans, sum);
    }

    cout << ans << endl;
    return 0;
}
