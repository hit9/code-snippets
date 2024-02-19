#include <cstdio>

using namespace std;

int n, r, j = 0;  // j 是选了几个
int chosen[22];

void p() {
    for (int i = 1; i <= j; i++) printf("%3d", chosen[i]);
    if (j > 0) putchar('\n');
}

// dfs 解决 [k..n] 上的问题
void dfs(int k) {
    // 剪枝: 如果选的超过 r 个, 或者算上剩余的也不足 r 个, 及时截止
    if (j > r || j + (n - k + 1) < r) return;
    if (k > n && j == r) p();  // 当前考虑了所有数字, 且正好够 r 个, 输出

    chosen[++j] = k;  // 选 k
    dfs(k + 1);       // 继续 k+1..n 的子问题
    j--;              // 撤销

    dfs(k + 1);  // 不选 k, 继续 k+1..n 的子问题
}

int main(void) {
    scanf("%d%d", &n, &r);
    dfs(1);  // [1..n] 的问题
    return 0;
}
