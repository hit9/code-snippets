// cc heap.c main.c
// ./a.out

#include <stdio.h>  // for printf

#include "heap.h"

int main(void) {
    int n = 6;
    int a[32] = {3, 1, 2, 7, 0, 4};

    // 堆化
    Build(a, n);

    // 插入
    n = Push(a, n, 6);

    // 堆顶
    int min = Top(a);

    // 不断弹出并打印
    while (n > 0) {
        int v = Pop(a, n--);
        printf("%d ", v);
    }
    return 0;
}
