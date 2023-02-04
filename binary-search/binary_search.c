// 二分查找算法
// https://writings.sh/post/algorithm-binary-search

#include <stdio.h>

// 从给定的大小为 n 的数组 a 中查找 target.
// 返回 target 的位置，如果找不到，返回 -1.
int BinarySearch(int a[], int n, int target) {
    int low = 0;
    int high = n - 1;

    int mid = 0;

    while (low <= high) {
        mid = (low + high) / 2;

        if (a[mid] < target) {
            // 目标值更大，让低位大一些，以缩小查找范围
            low = mid + 1;
        } else if (a[mid] > target) {
            // 目标值更小，让高位小一些，以缩小查找范围
            high = mid - 1;
        } else {
            // 恰好相等
            return mid;
        }
    }

    // 未找到
    return -1;
}

// 测试函数
int main(void) {
    int a[9] = {1, 3, 4, 6, 7, 8, 10, 13, 14};

    printf("Search 4 in a: %d\n", BinarySearch(a, 9, 4));    // Expect: 2
    printf("Search 12 in a: %d\n", BinarySearch(a, 9, 12));  // Expect: -1
    return 0;
}
