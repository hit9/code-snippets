// 归并排序 - 递归版

#include <stdio.h>  // for printf

void Merge(int a[], int tmp[], int start, int end) {
    if (start >= end) return;

    int start1 = start;
    int end1 = start + (end - start) / 2;

    int start2 = end1 + 1;
    int end2 = end;

    // 归并两边
    Merge(a, tmp, start1, end1);
    Merge(a, tmp, start2, end2);

    // 合并到 tmp
    int i = start1;
    int j = start2;
    int k = start;

    while (i <= end1 && j <= end2) tmp[k++] = a[i] <= a[j] ? a[i++] : a[j++];
    while (i <= end1) tmp[k++] = a[i++];
    while (j <= end2) tmp[k++] = a[j++];

    // 拷贝 tmp => a
    for (int i = start; i <= end; i++) a[i] = tmp[i];
}

void MergeSort(int a[], int n) {
    int tmp[n];
    Merge(a, tmp, 0, n - 1);
}

int main(void) {
    int n = 9;
    int a[] = {4, 1, 3, 9, 7, 2, 6, 8, 5};
    MergeSort(a, n);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
}
