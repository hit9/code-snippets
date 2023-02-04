// 从数组中原地删除所有元素
// https://writings.sh/post/algorithm-inplace-operations-on-array

#include <stdio.h>

// 从长度为 n 的数组中原地删除给定元素 k
// 不断把尾巴元素拣过来覆盖 k 元素
int RemoveInplace(int arr[], int n, int k) {
    int i = 0;

    while (i < n) {
        if (arr[i] == k) {
            arr[i] = arr[n - 1];
            n--;
        } else {
            i++;
        }
    }
    return n;
}

int main(void) {
    int arr1[] = {1, 3, 3, 2, 3, 4, 5, 3, 4};
    int k1 = RemoveInplace(arr1, 9, 3);
    for (int i = 0; i < k1; i++) printf("%d ", arr1[i]);
    printf("\n");

    int arr2[] = {1, 3, 3, 2, 3, 4, 5, 3, 4};
    int k2 = RemoveInplace(arr2, 9, 3);
    for (int i = 0; i < k2; i++) printf("%d ", arr2[i]);
    printf("\n");

    int arr3[] = {1, 3, 3, 2, 3, 4, 5, 3, 4};
    int k3 = RemoveInplace(arr3, 9, 3);
    for (int i = 0; i < k3; i++) printf("%d ", arr3[i]);
    printf("\n");
}
