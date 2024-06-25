// https://www.luogu.com.cn/problem/P6466
// P6466 分散层叠算法(Fractional Cascading)

#include <cstdio>
#include <cstring>

const int N = 10001;
const int K = 101;

int L[K][N];  // 原始的 k 个有序序列, 从下表 1 开始

struct V {
    int x;      // 元素值
    int y = 0;  // 在 L[i] 中出现的位置
    int z = 0;  // 在 M[i+1] 中出现的位置
};

V M[K][2 * N];  // 构造的 k 个序列, 从下表 1 开始
int SZ[K];      // 记录 M[i] 的长度

int ans[K];  // 记录一次询问在每个序列中的答案

int n, k, q, d;  // 问题中的所有参数

// 把 M1 每隔一个元素取样, 然后和 Li 归并到 M2 中去
// Li 的起始结束是 start1, end1
// M1 的起始结束是 start2, end2
// M2 的起始是 start
// 返回 start, 即最终 M2 的大小
int merge(int *Li, V *M1, V *M2, int start1, int end1, int start2, int end2,
          int start) {
    auto take1 = [&]() {  // 取 Li 的数值
        M2[start].x = Li[start1];
        M2[start].y = start1;
        M2[start].z = M1[start2 - 1].x >= Li[start1] ? (start2 - 1) : start2;
        start++;
        start1++;
    };
    auto take2 = [&]() {  // 取 M1 的数值
        M2[start].x = M1[start2].x;
        M2[start].y = start1;
        M2[start].z = start2;
        start++;
        start2 += 2;  // 间隔取样
    };
    while (start1 <= end1 && start2 <= end2)
        Li[start1] <= M1[start2].x ? take1() : take2();
    while (start1 <= end1) take1();
    while (start2 <= end2) take2();
    return start;
}

// 预处理
void preprocess() {
    memset(M, 0, sizeof(M));
    memset(SZ, 0, sizeof(SZ));

    // M[k] 即 L[k] 序列本身
    for (int j = 1; j <= n; j++) {
        M[k][j].x = L[k][j];
        M[k][j].y = j;
    }

    // 自后向前, 归并 M[i+1] 的一半和 L[i] 来构造 M[i]
    SZ[k] = n;
    for (int i = k - 1; i > 0; --i) {
        // start2: 从 2 开始间隔采样
        // 最终大小是 start2-1
        SZ[i] = merge(L[i], M[i + 1], M[i], 1, n, 2, SZ[i + 1], 1) - 1;
    }
}

// 处理一次询问
void query(int x) {
    memset(ans, 0, sizeof(ans));
    // 首先对 M[1] 二分查找 >= x 的左界
    int l = 1, r = SZ[1];
    while (l < r) {
        int m = (l + r) >> 1;
        if (M[1][m].x >= x)
            r = m;
        else
            l = m + 1;
    }
    // 记录 L[1] 的答案, 位于位置 y
    V *v = &M[1][l];
    // 注意验证合法性, 有可能不存在后继
    if (v->x >= x) ans[1] = L[1][v->y];
    // 对 i+1 的情况
    for (int i = 1; i < k; i++) {
        // 求解答案 ans[i+1]
        // z-2 位置的数值一定严格小于 x
        // 要么是 z 要么是 z-1 处
        if (M[i + 1][v->z - 1].x >= x || v->z > SZ[i + 1]) {
            // z-1 处是否是一个可行的后继?
            // 注意 z 肯定 >= 2, 所以 z-1 不会出问题
            // 或者 z 超过了大小限制时, 只好沿用 z-1
            v = &M[i + 1][v->z - 1];
        } else {
            // 否则就是 z 处
            v = &M[i + 1][v->z];
        }
        // 但是要注意验证后继的合法性
        if (L[i + 1][v->y] >= x) ans[i + 1] = L[i + 1][v->y];
    }
}

int main(void) {
    scanf("%d%d%d%d", &n, &k, &q, &d);

    // 输入 k 个有序序列
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &L[i][j]);
        }
    }

    // 预处理
    preprocess();

    // debug
    // for (int i = 1; i <= k; i++) {
    //     for (int j = 1; j <= SZ[i]; j++) {
    //         printf("%d[%d,%d] ", M[i][j].x, M[i][j].y, M[i][j].z);
    //     }
    //     printf("\n");
    // }

    int sum = 0;  // 每次询问的异或和
    int x;
    for (int i = 1; i <= q; i++) {
        // 获取本次的查询 x, 并解密
        scanf("%d", &x);
        x ^= sum;
        // 执行查询, 填充 ans 数组
        query(x);
        // 求解 ans 数组的异或和
        sum = 0;
        for (int j = 1; j <= k; j++) sum ^= ans[j];
        if (i % d == 0) printf("%d\n", sum);
    }
    return 0;
}
