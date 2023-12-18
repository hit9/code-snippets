
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;
using ull = unsigned long long;

const int N = 1000000 + 10;

// a 是原数组
int a[N];
// A 是 a[i]-i, 转化为求非降 B
int A[N];
// B[i] 是构造的非降数组
int B[N];

void solve(int n) {
    priority_queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(A[i]);
        q.push(A[i]);
        B[i] = q.top();  // 规模为 i 时的最优结尾
        q.pop();
    }
    for (int i = n - 1; i; i--) B[i] = min(B[i], B[i + 1]);
    return;
}

int main(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        A[i] = a[i] - i;
    }

    solve(n);

    // 构造回 B[i]+i
    for (int i = 1; i <= n; i++) B[i] += i;
    // 计算答案
    ull ans = 0;
    for (int i = 1; i <= n; i++) ans += abs(a[i] - B[i]);
    cout << ans << endl;
    for (int i = 1; i <= n; i++) cout << B[i] << " ";
    cout << endl;

    return 0;
}
