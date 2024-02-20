#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1000000 + 5;
char s[N];
int f[N];  // f[i] 表示以 i 结尾的最大长度

void calc(int i, char l, char r) {
    if (s[i] == r) {
        // [ .. f(j) .. ] j [... f(i-1)... ] i
        int j = i - 1 - f[i - 1];
        if (s[j] == l) {
            f[i] = f[i - 1] + 2;
            if (j >= 1) f[i] += f[j - 1];
        }
    }
}

void solve() {
    int mx = 0, mi = 0;
    for (int i = 1; s[i]; i++) {
        calc(i, '(', ')');
        calc(i, '[', ']');
        if (mx < f[i]) {
            mx = f[i];
            mi = i;
        }
    }
    for (int i = mi - mx + 1; i <= mi; i++) putchar(s[i]);
}

int main(void) {
    memset(s, 0, sizeof s);
    memset(f, 0, sizeof f);
    scanf("%s", s + 1);
    solve();
    return 0;
}
