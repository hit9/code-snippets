#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main(void) {
    int n;
    cin >> n;
    getchar();

    vector<int> a(n);

    for (int i = 0; i < n; i++) cin >> a[i];

    getchar();

    stack<int> s;
    vector<int> b(n, 0);

    for (int i = 0; i < n; i++) {
        while (!s.empty() && a[s.top()] < a[i]) {
            b[s.top()] = i + 1;
            s.pop();
        }
        s.push(i);
    }

    for (int i = 0; i < n; i++) cout << b[i] << " ";
    cout << endl;
    return 0;
}
