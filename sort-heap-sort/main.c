// 堆排序

#include <stdio.h>  // for printf

// 声明

void HeapBuild(int a[], int n);
int HeapPop(int a[], int n);

// 堆排序

// 从小到大原地堆排序
// 建立最大堆，弹出头，放到尾
void HeapSort(int a[], int n) {
    HeapBuild(a, n);
    while (n > 0) {
        // 取出顶元素
        int v = HeapPop(a, n--);
        a[n] = v;  // 放到最后面
    }
}

int main(void) {
    int n = 8;
    int a[] = {3, 1, 2, 7, 0, 4, 8, 9};

    HeapSort(a, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
}

// 最大堆实现
// https://writings.sh/post/data-structure-heap-and-common-problems

// Swap 交换数组 a 的位置 i 和 j
void Swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

// 从位置 i 开始下沉大小为 n 的堆
void HeapDown(int a[], int n, int i) {
    while (1) {
        // 左孩子 j1
        int j1 = 2 * i + 1;
        if (j1 >= n) break;

        // 右孩子 j2 （可能不存在）
        int j2 = j1 + 1;

        // j 是其中值更大的孩子
        int j = j1;
        if (j2 < n && a[j2] > a[j1]) j = j2;

        if (a[i] >= a[j]) break;
        Swap(a, i, j);
        i = j;
    }
}

// 将大小为 n 的数组 a 堆化 => 最大堆
void HeapBuild(int a[], int n) {
    // 从最后一层父节点，不断下沉堆
    for (int i = (n - 1) / 2; i >= 0; i--) {
        HeapDown(a, n, i);
    }
}

// 从大小为 n 的堆 a 中移除堆顶元素
// 返回移除的元素
// 如果堆空，返回 -1
int HeapPop(int a[], int n) {
    if (n <= 0) return -1;
    n--;
    Swap(a, 0, n);
    HeapDown(a, n, 0);  // 下沉
    return a[n];
}
