#include <stdio.h>

void Swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

// 原地分割数组，使得 < k 的数在左边， = k 的在中间， > k 的在右边
// [3 4 5 1 2 6 7] k = 4
// => [3 1 2 4 5 6 7]
void PartitionInplace(int arr[], int n, int k) {
    int left = 0;       // < k
    int right = n - 1;  // > k
    int i = 0;

    while (i <= right) {
        if (arr[i] > right) {
            Swap(arr, i, right);
            right--;
        } else if (arr[i] < k) {
            Swap(arr, i, left);
            left++;
            i++;
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

    int arr4[] = {7, 4, 6, 1, 1, 2, 2, 5, 5, 3, 8, 4, 4, 5};
    PartitionInplace(arr4, 14, 4);
    for (int i = 0; i < 14; i++) printf("%d ", arr4[i]);
    printf("\n");
}
