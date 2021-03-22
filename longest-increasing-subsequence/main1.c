// 最长递增子序列
// https://writings.sh/post/algorithm-longest-increasing-subsequence

#include <assert.h>  // for assert
#include <stdio.h>   // for printf

#define max(x, y) (x) > (y) ? (x) : (y)

// 返回长度为 n 的数组 a 的最长递增子序列的长度
int LongestIncreasingSubsequence(int a[], int n) {
    if (n == 0) return 0;

    // dp[i] 代表以位置 i 结尾的最长递增子序列的长度
    int dp[n];
    dp[0] = 1;

    // 记录 dp 中最大值
    int maxdp = dp[0];

    for (int i = 1; i < n; i++) {
        dp[i] = 1;  // 至少为 1
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxdp = max(dp[i], maxdp);
    }
    return maxdp;
}

int main(void) {
    int a1[9] = {3, 2, 9, 5, 3, 7, 8, 2};
    assert(LongestIncreasingSubsequence(a1, 9) == 4);

    int a2[8] = {10, 9, 2, 5, 3, 7, 101, 18};
    assert(LongestIncreasingSubsequence(a1, 9) == 4);

    return 0;
}
