// 最短编辑距离
// https://writings.sh/post/algorithm-minimum-edit-distance
// https://leetcode-cn.com/problems/edit-distance/

#include <assert.h>  // for assert
#include <string.h>  // for strlen

#define MIN(x, y) ((x) < (y) ? (x) : (y))

// 返回将字符串 a 编辑为字符串 b 的最短编辑步数
// 一次编辑可以是：删除一个字符、插入一个字符、替换一个字符
// 例如把 "horse" 编辑为 "ros" 的最少步数是 3
// 第一步是 "horse" -> "rorse"  （'h' 替换为 'r'）
// 第二步是 "rorse" -> "rose"  （删除第二个 'r'）
// 第三步是 "rose" -> "ros"  （删除 'e'）
// 采用动态规划方法
int MinEditDistance(char *a, char *b) {
    int m = strlen(a);
    int n = strlen(b);

    // 为处理边界方便，假设对字符串头部插入 $ 符号
    // horse => $horse
    // ros => $ros
    // 如此一来，dp[i][j] 的意思是，a[..i-1] 编辑到 b[..j-1] 的最小编辑距离
    int dp[m + 1][n + 1];

    // horse => $ 的编辑距离显然是：删除 5 个字符
    // 即 dp[i][0] => i
    for (int i = 0; i < m + 1; i++) dp[i][0] = i;

    // $ => ros 的编辑距离显然是：插入三个字符
    // 即 dp[0][j] = j
    for (int j = 0; j < n + 1; j++) dp[0][j] = j;

    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            // 在 a[..i-1] => b[..j-2] 的基础上，再插入一个字符 b[j-1] 得到
            // 即表格左方值 + 1 得到
            int left = dp[i][j - 1] + 1;

            // 在 a[..i-2] => b[..j-1] 的基础上，再删除一个字符 a[i-1] 得到
            // 即表格上方值 + 1 得到
            int up = dp[i - 1][j] + 1;

            // 考虑左上方的数字
            int left_up;

            if (a[i - 1] == b[j - 1]) {
                // 末尾两个字符相等
                // a[..i-1] => b[..j-1] 等价于 a[..i-2] => b[..j-2]
                left_up = dp[i - 1][j - 1];
            } else {
                // 否则，需要替换一次
                left_up = dp[i - 1][j - 1] + 1;
            }

            // 取三种方案的最小值
            dp[i][j] = MIN(MIN(left, up), left_up);
        }
    }
    return dp[m][n];
}

int main(void) {
    assert(MinEditDistance("horse", "ros") == 3);
    assert(MinEditDistance("intention", "execution") == 5);
    assert(MinEditDistance("simple", "example") == 3);
    return 0;
}
