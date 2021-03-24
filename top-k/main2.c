// topk 问题 - 找出无序数组中的最大的 k 个数
// https://writings.sh/post/algorithm-topk-and-median

// 快速选择方法

#include <stdio.h>  // for printf

void Swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

// 数组原地分割，取 a[start] = p
// >p 在左，=p 在中，<p在右
int Partition(int a[], int start, int end) {
    int p = a[start];
    int left = start;
    int right = end;
    int i = start;
    while (i <= right) {
        if (a[i] > p) {
            Swap(a, i, left);
            left++;
            i++;
        } else if (a[i] < p) {
            Swap(a, i, right);
            right--;
        } else {
            i++;
        }
    }
    return i;
}

void QuickSelect(int a[], int start, int end, int k) {
    if (start >= end) return;

    int m = Partition(a, start, end);

    if (k < m)
        QuickSelect(a, start, m - 1, k);
    else if (k > m)
        QuickSelect(a, m, end, k - m);
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
