// 从数组中原地删除所有元素
// https://writings.sh/post/algorithm-inplace-operations-on-array

#include <stdio.h>

// 从长度为 n 的数组中原地删除给定元素 k
// 思路：不断地把非 k 的元素拣到左边来
int RemoveInplace(int arr[], int n, int k) {
    int count = 0;
    int i = 0;
    while (i < n) {
        if (arr[i] != k) {
            // 拣到左边来，计数++
            arr[count] = arr[i];
            count++;
        }  // 否则忽略
        i++;
    }
    return count;
}

int main(void) {
    int arr1[] = {1, 3, 3, 2, 3, 4, 5, 3, 4};
    int k1 = RemoveInplace(arr1, 9, 3);
    for (int i = 0; i < k1; i++) printf("%d ", arr1[i]);
    printf("\n");

    return 0;
}
