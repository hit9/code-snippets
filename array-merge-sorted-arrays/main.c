// 合并两个有序数组

#include <stdio.h>

// 合并两个从小到大有序数组 a + b => c
// 使得 c 也是有序的
void MergeSortedArrays(int a[], int m, int b[], int n, int c[]) {
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < m && j < n) {
        if (a[i] <= b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    }
    while (i < m) c[k++] = a[i++];
    while (j < n) c[k++] = b[j++];
}

int main(void) {
    int m = 3;
    int a[] = {1, 2, 5};
    int n = 4;
    int b[] = {2, 3, 6, 7};
    int c[m + n];
    MergeSortedArrays(a, m, b, n, c);
    for (int i = 0; i < m + n; i++) printf("%d ", c[i]);
}
