// 蓄水池抽样

// 从 N 个数字机会均等的随机的抽取 K 个数字
// 从未知大小的数据流中机会均等的抽取 K 个数字

// 问题的根本：一次遍历，随机抽取

#include <stdio.h>   // for printf
#include <stdlib.h>  // for stdlib

// 辅助函数 （针对 C 语言）
// 生成范围 [low, high] 内的随机整数
int RandInt(int low, int high) { return (rand() % (high - low + 1)) + low; }

// 从数组 a 中随机抽取 K 个数字
// 结果输出到数组 b 中，其空间大小是 k
void RandomSampling(int n, int a[n], int k, int b[k]) {
    // 先把头 k 个元素放入 b
    for (int i = 0; i < k; i++) b[i] = a[i];
    // 剩下的数以 k/i 的概率替换 b 中的任意一个数字
    for (int i = k + 1; i < n; i++) {
        int j = RandInt(0, i);
        if (j < k) {  // 即 r=j/i < k/i
            b[j] = a[i];
        }
    }
}

int main(void) {
    int n = 100;
    int a[n];
    for (int i = 0; i < n; i++) a[i] = i;

    int k = 10;
    int b[k];
    RandomSampling(n, a, k, b);

    for (int i = 0; i < k; i++) printf("%d ", b[i]);
    return 0;
}
