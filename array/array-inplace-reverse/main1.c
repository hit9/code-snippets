#include <stdio.h>

void Swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void ReverseInplace(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) Swap(arr, i, n - 1 - i);
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    ReverseInplace(arr1, 9);
    for (int i = 0; i < 9; i++) printf("%d ", arr1[i]);
    printf("\n");

    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ReverseInplace(arr2, 10);
    for (int i = 0; i < 10; i++) printf("%d ", arr2[i]);
    printf("\n");
    return 0;
}
