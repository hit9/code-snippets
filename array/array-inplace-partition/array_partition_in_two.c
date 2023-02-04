// 原地分割数组（两份）
// https://writings.sh/post/algorithm-inplace-operations-on-array

#include <stdio.h>

// Swap 交换数组 arr 的第 i 和 j 项元素
void Swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

// 原地分割数组，使得 <= k 的数在左边， > k 的在右边
// 返回左边的数据多少。
int PartitionInplace(int arr[], int n, int k) {
    int left = 0;       // 左边集合的上界
    int right = n - 1;  // 右边集合的下界

    while (left <= right) {
        if (arr[left] <= k) {
            left++;
        } else {
            if (left != right) Swap(arr, left, right);
            right--;
        }
    }
    return left;
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
