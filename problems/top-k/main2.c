// topk 问题 - 找出无序数组中的最大的 k 个数
// https://writings.sh/post/algorithm-topk

// 快速选择方法

#include <stdio.h>  // for printf

void Swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

// 数组原地分割，取 v = a[start]
// >v 在左，=v 在中，<v在右
// 返回基准元素在整个数组中的位置
// 和快排完全一样
int Partition(int a[], int start, int end) {
    int v = a[start];
    int left = start;
    int right = end;
    int i = start;
    while (i <= right) {
        if (a[i] > v) {
            Swap(a, i, left);
            left++;
            i++;
        } else if (a[i] < v) {
            Swap(a, i, right);
            right--;
        } else {
            i++;
        }
    }
    return i - 1;
}

void QuickSelect(int a[], int start, int end, int k) {
    if (start >= end || k <= 0) return;

    int p = Partition(a, start, end);
    int m = p + 1;  // 整个数组中在基准元素左边的元素个数

    if (k < m)
        QuickSelect(a, start, p - 1, k);
    else if (k > m)
        QuickSelect(a, p + 1, end, k);  // 注意传 k 而非 k - m ，对齐 m 的意义
    else
        return;
}

// 采用不断分区的办法，找出给定数组中的最大的 k 个数
// 输入原大小为 n 的数组 a
// 函数会原地把 k 大数放到 a 的前 k 个
void TopK(int a[], int n, int k) { return QuickSelect(a, 0, n - 1, k); }

int main(void) {
    int n = 8;
    int k = 3;
    int a[] = {5, 1, 2, 4, 8, 7, 9, 13};

    TopK(a, n, k);

    for (int i = 0; i < k; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}
