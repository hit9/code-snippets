// 给出最长回文子序列 - 打印所有回文子序列 - 动态规划方法
// http://writings.sh/post/algorithm-longest-palindromic-subsequence

#include <assert.h>  // for assert
#include <stdio.h>   // for printf
#include <string.h>  // for strlen

#define max(a, b) (a) > (b) ? (a) : (b)

#define FROM_INIT 0         // 0
#define FROM_LEFT 1         // 0b001
#define FROM_BOTTOM 2       // 0b010
#define FROM_LEFT_BOTTOM 4  // 0b100

// 计算长度为 n 的字符串 s 的最长公共子序列的长度
// 填充给定的 dp 数组 和 path 数组。
void ProcessLongestPalindromicSubsequence(char *s, int n, int dp[n][n],
                                          int path[n][n]) {
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            dp[i][j] = 1;

            if (s[i] == s[j]) {
                // 优先判断 FROM_LEFT_BOTTOM
                if (i + 1 <= j - 1) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = j - i + 1;
                }
                if (j != i) path[i][j] = FROM_LEFT_BOTTOM;
            } else {
                if (i + 1 < n) dp[i][j] = max(dp[i][j], dp[i + 1][j]);
                if (j - 1 >= 0) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }

            // 无论前面进入的哪个分支，
            // 都可以以「或」的方式补上左方 或 右方来源的可能。
            if (i + 1 < n && dp[i][j] == dp[i + 1][j] && i != j) {
                path[i][j] |= FROM_BOTTOM;
            }
            if (j - 1 >= 0 && dp[i][j] == dp[i][j - 1] && i != j) {
                path[i][j] |= FROM_LEFT;
            }
        }
    }
}

// DFS 深度优先遍历 path 数组
// 输入的 i,j 是当前的方格位置
// depth 是当前迭代的深度，初始顶级节点depth=1
// parents 是所有父节点需要打印的字符
void DFS(char *s, int n, int path[n][n], int i, int j, int depth,
         char parents[depth]) {
    if (path[i][j] & FROM_LEFT_BOTTOM) {
        // 回文序列得到扩充的情况，需要打印
        // 此时 s[i] == s[j]
        parents[depth] = s[j];
        // 此处只收集了右边字符 s[j]
        // 左边的镜像字符 s[i] 需要晚些打印
    } else if (path[i][j] == FROM_INIT) {
        // 打印的构成
        // abcba => [ab] [c] [ba] 即 parents + 单字符 + 逆序parents
        // 或 abba => [ab] [ba] 即中间无单个字符的打印
        for (int t = 0; t <= depth; t++)  // 正序打印 parents
            if (parents[t] != '\0') printf("%c", parents[t]);

        // 打印 FROM_INIT 处的单个字符
        if (i == j) printf("%c", s[i]);

        for (int t = depth; t >= 0; t--)  // 逆序打印 parents
            if (parents[t] != '\0') printf("%c", parents[t]);

        printf("\n");  // 换行表示找到了一个最长回文序列
    } else {
        parents[depth] = '\0';
    }

    // 向左 DFS
    if (path[i][j] & FROM_LEFT) DFS(s, n, path, i, j - 1, depth + 1, parents);
    // 向下 DFS
    if (path[i][j] & FROM_BOTTOM) DFS(s, n, path, i + 1, j, depth + 1, parents);
    // 向左下 DFS
    if (path[i][j] & FROM_LEFT_BOTTOM)
        DFS(s, n, path, i + 1, j - 1, depth + 1, parents);
}

// 打印给定字符串的所有最长回文子序列。
void PrintAllLongestPalindromicSubsequence(char *s) {
    int n = strlen(s);
    if (n <= 0) return;

    // dp[i][j] 表示子串 i..j 内的最长回文序列长度
    int dp[n][n];
    // path[i][j] 表示 dp[i][j] 的填写是从哪个方格而来
    int path[n][n];

    // 对所有 i, j 进行初始化 0 是必要的：
    // 因为在 DP 过程中，s[i] == s[j] 的边界情况
    // 可以认为是 FROM_LEFT_BOTTOM 的一种，视作 0 + 2 => 2
    // 这要求对 j < i 的 path[i][j] 也要有合理的值 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) path[i][j] = FROM_INIT;

    // 动态规划处理
    ProcessLongestPalindromicSubsequence(s, n, dp, path);

    // dp[0][n-1] 就是最长的回文子序列长度
    int k = dp[0][n - 1];

    // 父节点需要打印的字符，无则是 '\0'
    char parents[k];
    // 当前深度
    int depth = 0;

    //从 i=0, j=n-1 开始 DFS path 数组
    parents[depth++] = '\0';
    DFS(s, n, path, 0, n - 1, depth, parents);
}

int main(void) {
    PrintAllLongestPalindromicSubsequence("ababdab");
    printf("============  \n");  // 分隔符
    PrintAllLongestPalindromicSubsequence("ababbdab");
    printf("============  \n");  // 分隔符
    PrintAllLongestPalindromicSubsequence("abca");
    printf("============  \n");  // 分隔符
    PrintAllLongestPalindromicSubsequence("abbcca");
    printf("============  \n");  // 分隔符
    return 0;
}
