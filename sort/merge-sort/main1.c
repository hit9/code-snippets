// 归并排序 - 循环版

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

// 归并排序循环版
void MergeSort(int a[], int n) {
    int tmp[n];
    for (int i = 0; i < n; i++) tmp[i] = 0;

    // k=1 每1个归并一次..
    // k=2 每2个归并一次..
    // k=4 每4个归并一次..
    // k=8 每8个归并一次..
    for (int k = 1; k < n; k *= 2) {
        // 两两 k=1 归并 [0,0]+[1,1], [2,2]+[3,3] ..
        // 两两 k=2 归并 [0,1]+[2,3], [4,5]+[6,7] ..
        // 两两 k=4 归并 [0,3]+[4,7], [8,11]+[12,15] ..
        for (int start = 0; start < n; start += 2 * k) {
            int start1 = start;
            int end1 = start + k - 1;
            if (end1 > n - 1) end1 = n - 1;

            int start2 = end1 + 1;
            int end2 = start2 + k - 1;
            if (end2 > n - 1) end2 = n - 1;

            // 合并
            MergeSortedArrays(a, start1, end1, a, start2, end2, tmp, start);
            // 拷贝
            for (int i = start1; i <= end2; i++) a[i] = tmp[i];
        }
    }
}

int main(void) {
    int n = 9;
    int a[] = {5, 3, 1, 9, 7, 2, 5, 8, 4};
    MergeSort(a, n);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
}
