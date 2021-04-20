// 洗牌算法

#include <stdio.h>   // for printf
#include <stdlib.h>  // for stdlib
#include <time.h>

// 辅助函数 （针对 C 语言）
// 生成范围 [low, high] 内的随机整数
int RandInt(int low, int high) { return (rand() % (high - low + 1)) + low; }

void Swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void Shuffle(int n, int a[n]) {
    for (int i = 0; i < n; i++) {
        Swap(a, i, RandInt(0, i));
    }
}

int main(void) {
    int n = 30;
    int a[n];
    for (int i = 0; i < n; i++) a[i] = i;

    srand(time(NULL));
    Shuffle(n, a);

    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}
