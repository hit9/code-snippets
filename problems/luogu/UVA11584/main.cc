#include <algorithm>
#include <deque>
#include <iostream>
#include <string>

using namespace std;

int solve(const string& s) {
    int n = s.size();
    int f[n + 1];
    f[0] = -1;
    deque<int> q;

    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] + 1;
        int k = q.size();
        while (k--) {
            int j = q.back();
            q.pop_back();
            if (j && s[j - 1] == s[i - 1]) {
                f[i] = min(f[i], f[j - 1] + 1);
                q.push_front(j - 1);
            }
        }
        q.push_front(i - 1);
        q.push_front(i);
    }

    return f[n] + 1;
}

int main(void) {
    int n;
    cin >> n;
    getchar();
    while (n--) {
        string s;
        getline(cin, s,'\n');
        cout << solve(s) << endl;
    }
    return 0;
}
