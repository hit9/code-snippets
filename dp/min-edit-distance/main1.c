// 最短编辑距离
// https://writings.sh/post/algorithm-minimum-edit-distance

#include <stdbool.h>  // for bool
#include <stdio.h>    // for printf
#include <string.h>   // for strlen

// 打印所有最短编辑方式

#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define FROM_INIT 0
#define FROM_LEFT 1             // 0b0001
#define FROM_UP 2               // 0b0010
#define FROM_LEFT_UP_REPLACE 4  // 0b0100
#define FROM_LEFT_UP_COPY 8     // 0b1000

typedef struct {
    int flag;  // 操作方式 1 插入 2 删除 3 替换
    char ch1;  // 操作的字符 1
    char ch2;  // 操作的字符 2, 针对替换操作, ch1 替换为 ch2
} Operation;

void PrintOperation(Operation *op) {
    if (op == NULL) return;
    if (op->flag == 0) return;
    if (op->flag == 1) printf("插入 %c\n", op->ch1);
    if (op->flag == 2) printf("删除 %c\n", op->ch1);
    if (op->flag == 3) printf("替换 %c => %c\n", op->ch1, op->ch2);
}

int DP(char *a, char *b, int m, int n, int dp[m + 1][n + 1],
       int path[m + 1][n + 1]) {
    for (int i = 0; i < m + 1; i++) {
        dp[i][0] = i;
        path[i][0] = FROM_INIT;
    }

    for (int j = 0; j < n + 1; j++) {
        dp[0][j] = j;
        path[0][j] = FROM_INIT;
    }

    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            path[i][j] = FROM_INIT;  // 初始化 path[i][j]

            int left = dp[i][j - 1] + 1;

            int up = dp[i - 1][j] + 1;

            int left_up;
            bool replace = false;

            if (a[i - 1] == b[j - 1]) {
                left_up = dp[i - 1][j - 1];
                replace = false;
            } else {
                left_up = dp[i - 1][j - 1] + 1;
                replace = true;
            }

            dp[i][j] = MIN(MIN(left, up), left_up);

            if (dp[i][j] == left) path[i][j] |= FROM_LEFT;
            if (dp[i][j] == up) path[i][j] |= FROM_UP;
            if (dp[i][j] == left_up) {
                if (replace)
                    path[i][j] |= FROM_LEFT_UP_REPLACE;
                else
                    path[i][j] |= FROM_LEFT_UP_COPY;
            }
        }
    }
    return dp[m][n];
}

// DFS 深度优先遍历 path 数组
// 输入的 i,j 是当前的方格位置
// depth 是当前递归深度，初始 depth = 1
// ops 是当前递归深度上的路径，即记录的编辑步骤序列
void DFS(char *a, char *b, int m, int n, int path[m + 1][n + 1], int i, int j,
         int depth, Operation ops[depth]) {
    Operation *op = &ops[depth - 1];  // 设置当前格的编辑方式

    if (path[i][j] & FROM_LEFT) {
        // 左边方格，插入一个字符 b[j-1] 而来
        op->flag = 1;
        op->ch1 = b[j - 1];
        // 向左 DFS
        DFS(a, b, m, n, path, i, j - 1, depth + 1, ops);
    }

    if (path[i][j] & FROM_UP) {
        // 上面方格，删除一个字符 a[i-1] 而来
        op->flag = 2;
        op->ch1 = a[i - 1];
        // 向上 DFS
        DFS(a, b, m, n, path, i - 1, j, depth + 1, ops);
    }

    if (path[i][j] & FROM_LEFT_UP_COPY || path[i][j] & FROM_LEFT_UP_REPLACE) {
        if (path[i][j] & FROM_LEFT_UP_REPLACE) {
            // 左上方格，替换 a[i-1] 到 b[j-1] 而来
            op->flag = 3;
            op->ch1 = a[i - 1];
            op->ch2 = b[j - 1];
        } else {
            // 拷贝而来，无需记录
            // 置 0 表示忽略
            op->flag = 0;
        }
        // 向左上 DFS
        DFS(a, b, m, n, path, i - 1, j - 1, depth + 1, ops);
    }

    if (i == 1 && j == 1) {
        // 反向打印 ops 序列
        for (int k = depth - 1; k >= 0; k--) PrintOperation(&ops[k]);
        // 打印结束
        printf("已结束一种编辑方式\n");
        return;
    }
}

// 打印把字符串 a 编辑为 b 的所有最短编辑方式
void PrintMinEditSteps(char *a, char *b) {
    int m = strlen(a);
    int n = strlen(b);

    // DP 数组
    int dp[m + 1][n + 1];
    // 路径数组
    int path[m + 1][n + 1];
    // 规划过程，返回最少步数 k
    DP(a, b, m, n, dp, path);
    // 记录一种最短编辑的操作序列
    Operation ops[m + n];
    // 记录当且递归深度
    int depth = 1;
    // 递归打印所有最短编辑的操作方式
    printf("编辑 %s 到 %s \n", a, b);
    DFS(a, b, m, n, path, m, n, depth, ops);
    printf("\n");
}

int main(void) {
    PrintMinEditSteps("horse", "ros");
    PrintMinEditSteps("simple", "example");
    PrintMinEditSteps("intention", "execution");
    return 0;
}
