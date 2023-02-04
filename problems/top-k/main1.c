// topk 问题 - 找出无序数组中的最大的 k 个数
// https://writings.sh/post/algorithm-topk

// 最小堆方法

#include <stdio.h>  // for printf

// 声明
void HeapBuild(int a[], int n);          // 堆化
int HeapReplace(int a[], int n, int v);  // 替换堆顶

// 采用最小堆，找出给定数组中的最大的 k 个数
// 输入原大小为 n 的数组 a
// 函数会原地把 k 大数放到 a 的前 k 个
void TopK(int a[], int n, int k) {
    if (n <= 0 || k <= 0 || k > n) return;

    // 前 k 个 数最小堆化
    HeapBuild(a, k);

    // 剩余的 k .. n-1 元素依次和堆顶比较
    for (int i = k; i < n; i++) {
        if (a[i] > a[0]) {
            // 如果比堆顶大，则替换堆顶
            HeapReplace(a, k, a[i]);
        }
    }
}

// 最终的堆顶元素即第 k 大的元素
int Kth(int a[], int n, int k) {
    TopK(a, n, k);
    return a[0];
}

int main(void) {
    int n = 8;
    int k = 3;
    int a[] = {5, 1, 2, 4, 8, 7, 9, 13};

    TopK(a, n, k);

    for (int i = 0; i < k; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");

    // 堆顶元素
    int a1[] = {5, 1, 2, 4, 8, 7, 9, 13};
    int kth = Kth(a1, n, k);
    printf("kth => %d ", kth);

    return 0;
}

// 堆实现

void Swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void HeapDown(int a[], int n, int i) {
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

void HeapBuild(int a[], int n) {
    // 从最后一层父节点，不断下沉堆
    for (int i = (n - 1) / 2; i >= 0; i--) {
        HeapDown(a, n, i);
    }
}

int HeapReplace(int a[], int n, int v) {
    if (n <= 0) return -1;
    int top = a[0];
    a[0] = v;
    HeapDown(a, n, 0);
    return top;
}
