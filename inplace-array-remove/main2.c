// 从数组中原地删除所有元素

#include <stdio.h>

void Swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

/* // 从长度为 n 的数组中原地删除给定元素 v */
/* int RemoveInplace(int arr[], int n, int v) { */
/*     int i = 0; */
/*     int j = n - 1; */

/*     while (i <= j) { */
/*         if (arr[j] == v) { */
/*             j--; */
/*         } else { */
/*             if (arr[i] == v) { */
/*                 Swap(arr, i, j); */
/*                 j--; */
/*             } */
/*             i++; */
/*         } */
/*     } */
/*     return i; */
/* } */

/* // 从长度为 n 的数组中原地删除给定元素 k */
/* // 不断把尾巴元素拣过来覆盖 k 元素 */
/* int RemoveInplace(int arr[], int n, int k) { */
/*     int i = 0; */

/*     while (i < n) { */
/*         if (arr[i] == k) { */
/*             arr[i] = arr[n - 1]; */
/*             n--; */
/*         } else { */
/*             i++; */
/*         } */
/*     } */
/*     return n; */
/* } */

// 从长度为 n 的数组中原地删除给定元素 k
// 从左到右，遇到 k 就从右边找一个非 k 的元素拣过来覆盖
int RemoveInplace(int arr[], int n, int k) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        // 右侧先准备好，找到一个非 k 的位置
        if (arr[right] == k) {
            right--;
            continue;
        }

        // 然后 left 才行动
        if (arr[left] == k) {
            // 遇到 k ，把右侧的非 k 元素拣过来覆盖
            arr[left] = arr[right];
            // 这个 right 已经用过，不再利用
            right--;
        }

        left++;
    }

    return left;
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
