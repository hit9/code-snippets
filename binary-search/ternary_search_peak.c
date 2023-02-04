// 三分法求单峰
// https://writings.sh/post/algorithm-golden-search

#include <stdio.h>

// 给出大小为 n 的数组 a 的单峰的下标位置。
int TernarySearchPeak(int a[], int n) {
    int low = 0;
    int high = n - 1;
    int delta = 0;

    int partition_left = 0;
    int partition_right = 0;

    while (low < high) {
        delta = (high - low) / 3;
        partition_left = low + delta;
        partition_right = high - delta;

        if (a[partition_left] < a[partition_right]) {
            high = partition_right - 1;
        } else if (a[partition_left] > a[partition_right]) {
            low = partition_left + 1;
        } else {
            low = partition_left + 1;
            high = partition_right - 1;
        }
    }

    return low;
}

int main(void) {
    int a[10] = {8, 6, 5, 4, 1, 2, 5, 7, 9, 13};
    int pos = ternary_search_peak(a, 10);
    int peak = a[pos];
    printf("ternary_search_peak of a: %d\n", peak);  // Expect: 1
    return 0;
}
