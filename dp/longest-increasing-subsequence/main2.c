// 最长递增子序列 - 打印所有最长递增子序列
// https://writings.sh/post/algorithm-longest-increasing-subsequence

#include <assert.h>  // for assert
#include <stdio.h>   // for printf

#define max(x, y) (x) > (y) ? (x) : (y)

// 返回长度为 n 的数组 a 的最长递增子序列的长度
int Process(int a[], int n, int dp[n], int path[n][n]) {
    if (n == 0) return 0;
    int maxdp = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = 1;

        // 记录本次从哪个 j 而来，可能有多个
        // k 是记录一个有多少个来源的 j
        int k = 0;

        for (int j = 0; j < i; j++) {
            if (a[i] > a[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        for (int j = 0; j < i; j++) {
            if (a[i] > a[j] && dp[i] == dp[j] + 1) {
                // 记录 j 为 i 的来源位置
                path[i][k++] = j;
            }
        }

        // 占位 -1 表示 dp[i] 是初始化而来
        if (k == 0) path[i][k++] = -1;

        // 末尾标识结束点
        path[i][k] = -2;

        maxdp = max(dp[i], maxdp);
    }
    return maxdp;
}

// DFS 深度优先反向追踪路径
// 输入的 z 是需要打印的字符，zn 是其大小
void DFS(int a[], int n, int i, int path[n][n], int z[], int zn) {
    if (i >= 0) {
        // 当前字符需要打印，用 z 栈收集
        z[zn++] = a[i];

        // 处理其所有的来源
        for (int k = 0; path[i][k] != -2; k++) {
            int j = path[i][k];  // 来源位置
            DFS(a, n, j, path, z, zn);
        }
    } else {
        // 需要结束收集，开始逆序打印
        while (zn != 0) printf("%d ", z[--zn]);
        printf("\n");  // 换行作为分割
    }
}

// 打印大小为 n 的数组 a 的所有最长递增子序列
void PrintAllLongestIncreasingSubsequence(int a[], int n) {
    int dp[n];

    // path[i][k] = j 表示 j 是 i 的来源位置
    int path[n][n];

    // 获取最大长度
    int L = Process(a, n, dp, path);

    // 记录需要打印的数字，是一个栈，正向收集，反向打印
    int z[L];
    int zn = 0;

    // 在 dp 数组中找最大长度，然后以其为起点 DFS
    for (int i = 0; i < n; i++) {
        if (dp[i] == L) DFS(a, n, i, path, z, zn);
    }
}

int main(void) {
    int a1[8] = {3, 2, 9, 5, 3, 7, 8, 2};
    PrintAllLongestIncreasingSubsequence(a1, 8);
    printf("----------\n");

    /* int a2[8] = {10, 9, 2, 5, 3, 7, 101, 18}; */
    /* PrintAllLongestIncreasingSubsequence(a2, 8); */
    /* printf("----------\n"); */

    /* int a3[4] = {7, 7, 7, 7}; */
    /* PrintAllLongestIncreasingSubsequence(a3, 4); */
    /* printf("----------\n"); */

    /* int a4[4] = {3, 6, 8, 7}; */
    /* PrintAllLongestIncreasingSubsequence(a4, 4); */
    /* printf("----------\n"); */
    return 0;
}
