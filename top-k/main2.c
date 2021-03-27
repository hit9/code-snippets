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
    // 返回的是: <=v 的元素个数
    return i;
}

void QuickSelect(int a[], int start, int end, int k) {
    if (start >= end || k <= 0) return;

    int m = Partition(a, start, end);
    int p = m - 1;  // 此时基准元素 v 的位置

    if (k < m)
        QuickSelect(a, start, p - 1, k);
    else if (k > m)
        // 注意此处传入是 k 而非 k-m
        // m 是整个数组上的基准位置 + 1 而得
        // k 需要和 m 比较，所以 k 是绝对的
        QuickSelect(a, p + 1, end, k);
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
