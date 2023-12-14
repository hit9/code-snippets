#include <iostream>
#include <queue>
#include <vector>

using namespace std;

using ull = unsigned long long;

ull solve(const vector<int> &a) {
    priority_queue<int> q;
    ull ans = 0;
    for (auto x : a) {
        q.push(x);
        q.push(x);
        ans += q.top() - x;
        q.pop();
    }
    return ans;
}

int main(void) {
    int n;
    cin >> n;
    getchar();
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << solve(a) << endl;
    return 0;
}
