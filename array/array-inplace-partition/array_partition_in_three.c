// 原地分割数组（三份）
// https://writings.sh/post/algorithm-inplace-operations-on-array

#include <stdio.h>

void Swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

// 原地分割数组，使得 < k 的数在左边， > k 的在右边, == k 的在中间。
void PartitionInplace(int arr[], int n, int k) {
    int left = 0;       // 左边集合的上界
    int right = n - 1;  // 右边集合的下界
    int i = 0;          // 中间元素的迭代变量

    while (i <= right) {
        if (arr[i] < k) {
            if (i != left) Swap(arr, left, i);
            left++;
            i++;
        } else if (arr[i] > k) {
            if (i != right) Swap(arr, right, i);
            right--;
        } else {
            i++;
        }
    }
}

int main(void) {
    int arr1[] = {7, 4, 6, 1, 2, 5, 3};
    PartitionInplace(arr1, 7, 4);
    for (int i = 0; i < 7; i++) printf("%d ", arr1[i]);
    printf("\n");

    int arr2[] = {7, 4, 6, 1, 2, 5, 3, 8};
    PartitionInplace(arr2, 8, 4);
    for (int i = 0; i < 8; i++) printf("%d ", arr2[i]);
    printf("\n");

    int arr3[] = {1, 6, 3, 2, 4, 5, 3, 2};
    PartitionInplace(arr3, 8, 3);
    for (int i = 0; i < 8; i++) printf("%d ", arr3[i]);
    printf("\n");

    int arr4[] = {7, 4, 6, 1, 1, 2, 2, 5, 5, 3, 8, 4, 4, 5};
    PartitionInplace(arr4, 14, 4);
    for (int i = 0; i < 14; i++) printf("%d ", arr4[i]);
    printf("\n");
}
