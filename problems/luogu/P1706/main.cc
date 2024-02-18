#include <cstdio>
using namespace std;

int a[10];
bool vis[10] = {false};
int path[10];
int n;
int j = 1;

void p() {
    for (int i = 1; i <= n; i++) {
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar('0' + path[i]);
    }
    putchar('\n');
}

void dfs() {
    if (j > n) {
        p();
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        vis[i] = true;
        path[j++] = a[i];
        dfs();
        j--;
        vis[i] = false;
    }
}

int main(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) a[i] = i;
    dfs();
    return 0;
}
