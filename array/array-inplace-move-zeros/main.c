// 将所有 0 原地移动到数组的右边，保序
// https://leetcode-cn.com/problems/move-zeroes
// 类似问题：http://writings.sh/post/algorithm-inplace-operations-on-array#%E5%8E%9F%E5%9C%B0%E5%88%A0%E9%99%A4%E6%95%B0%E7%BB%84%E5%85%83%E7%B4%A0

// 编译: cc main.c
// 执行: ./a.out

#include <stdio.h>  // for printf

// 把值等于 k 的元素移动到数组右边
// 其他元素的顺序要不变
void MoveKRight(int a[], int n, int k) {
    int count = 0;  // Count !=k elements
    int j = 0;
    while (j < n) {
        if (a[j] != k) {
            a[count] = a[j];
            count++;
        }
        j++;
    }

    // 剩余的刷 k
    while (count < n) a[count++] = k;
}

// 测试
int main(void) {
    int n = 5;
    int k = 0;
    int a[] = {0, 1, 0, 3, 5};
    MoveKRight(a, n, k);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}
