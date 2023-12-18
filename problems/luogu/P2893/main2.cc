#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int N = 2001;

// A 是原数组
int A[N];

int solve(int n) {
    int ans = 0;
    priority_queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(A[i]);
        q.push(A[i]);
        ans += q.top() - A[i];
        q.pop();
    }
    return ans;
}

int main(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];

    // 求非降情况
    int ans1 = solve(n);
    // 反向后求非增
    reverse(A + 1, A + n + 1);
    int ans2 = solve(n);
    cout << min(ans1, ans2) << endl;

    return 0;
}

