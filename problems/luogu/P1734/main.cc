#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1000 + 1;
int S;

int w[N];  // 价值数组
int f[N];  // 01 dp 数组

int solve() {
    memset(w, 0, sizeof w);

    // 预处理价值数组
    for (int i = 1; i <= S; i++) {
        // 注意不含其本身, 只算 1, 不算 i
        if (i > 1) w[i] += 1;
        // 2~sqrt(i)
        int j = 2;
        for (; j * j < i; j++) {
            if (i % j == 0) w[i] += j + i / j;
        }
        // sqrt(i)
        if (j * j == i) w[i] += j;
    }

    // 求 01 背包, 求最大价值和
    // 体积限制 S, 每个物品的体积 i, 价值 w[i]
    // 要求不同的数字, 所以每个数字只可以用一次
    memset(f, 0xcf, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= S; i++) {
        for (int j = S; j >= i; j--) {
            // 选 i or 不选
            f[j] = max(f[j], f[j - i] + w[i]);
        }
    }

    // 答案是 f 的最大值
    int ans = 0;
    for (int j = 0; j <= S; j++) ans = max(ans, f[j]);
    return ans;
}

int main(void) {
    scanf("%d", &S);
    printf("%d\n", solve());
    return 0;
}
