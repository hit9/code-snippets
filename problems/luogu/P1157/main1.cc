#include <cstdio>

// 这个是全组合

using namespace std;

int n, j = 0;  // j 是选了几个
int chosen[22];

void p() {
    for (int i = 1; i <= j; i++) printf("%3d", chosen[i]);
    if (j > 0) putchar('\n');
}

// dfs 解决 [k..n] 上的问题
void dfs(int k) {
    if (k > n) {  // 当前考虑了所有数字, 输出
        p();
        return;
    }

    chosen[++j] = k;  // 选 k
    dfs(k + 1);       // 继续 k+1..n 的子问题
    j--;              // 撤销

    dfs(k + 1);  // 不选 k, 继续 k+1..n 的子问题
}

int main(void) {
    scanf("%d", &n);
    dfs(1);  // [1..n] 的问题
    return 0;
}
