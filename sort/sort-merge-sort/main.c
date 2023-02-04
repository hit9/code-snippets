// 归并排序 - 递归版

#include <stdio.h>  // for printf

// 合并两个有序数组
void MergeSortedArrays(int a[], int start1, int end1, int b[], int start2,
                       int end2, int c[], int start3) {
    int i = start1;
    int j = start2;
    int k = start3;

    while (i <= end1 && j <= end2) {
        if (a[i] <= b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    }
    while (i <= end1) c[k++] = a[i++];
    while (j <= end2) c[k++] = b[j++];
}

// 递归合并过程
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
    MergeSortedArrays(a, start1, end1, a, start2, end2, tmp, start);

    // 拷贝 tmp => a
    for (int i = start; i <= end; i++) a[i] = tmp[i];
}

// 归并排序：输入数组和大小
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
