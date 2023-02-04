#include "heap.h"

///////////
// 实现
///////////

// 从位置 j 开始上浮堆 O(logn)
void Up(int a[], int j) {
    while (j > 0) {
        // 父节点
        int i = (j - 1) / 2;
        if (a[i] <= a[j]) break;
        Swap(a, i, j);
        j = i;
    }
}

// 从位置 i 开始下沉大小为 n 的堆 O(logn)
void Down(int a[], int n, int i) {
    while (1) {
        // 左孩子 j1
        int j1 = 2 * i + 1;
        if (j1 >= n) break;

        // 右孩子 j2 （可能不存在）
        int j2 = j1 + 1;

        // j 是其中值更小的孩子
        int j = j1;
        if (j2 < n && a[j2] < a[j1]) j = j2;

        if (a[i] <= a[j]) break;
        Swap(a, i, j);
        i = j;
    }
}

// 将大小为 n 的数组 a 堆化  O(n)
void Build(int a[], int n) {
    // 从最后一层父节点，不断下沉堆
    for (int i = (n - 1) / 2; i >= 0; i--) {
        Down(a, n, i);
    }
}

// 获取堆顶元素  O(1)
int Top(int a[]) { return a[0]; }

// 向大小为 n 的堆 a 中添加元素 v
// 返回添加后的数组大小
// O(logn)
int Push(int a[], int n, int v) {
    a[n] = v;
    Up(a, n);  // 上浮
    return ++n;
}

// 从大小为 n 的堆 a 中移除堆顶元素
// 返回移除的元素
// 如果堆空，返回 -1
// O(logn)
int Pop(int a[], int n) {
    if (n <= 0) return -1;
    n--;
    Swap(a, 0, n);
    Down(a, n, 0);  // 下沉
    return a[n];
}

// 替换堆顶元素为 v
// 返回原堆顶元素
// 如果堆空，返回 -1
// 相对 Pop + Push 更快一些
int Replace(int a[], int n, int v) {
    if (n <= 0) return -1;
    int top = a[0];
    a[0] = v;
    Down(a, n, 0);
    return top;
}

// Swap 交换数组 a 的位置 i 和 j
void Swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
