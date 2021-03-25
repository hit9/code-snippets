// 快速排序 - 循环版本

#include <stdio.h>  // for printf

void Swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

// 分割函数，选取第一个为基准元素
// 把 start 到 end 内的元素，小于基准元素的放在左边，大于的放在右边
// 返回基准值的最右位置
int Partition(int a[], int start, int end) {
    int k = a[start];
    int left = start;
    int right = end;
    int i = start;

    while (i <= right) {
        if (a[i] < k) {
            Swap(a, i, left);
            left++;
            i++;
        } else if (a[i] > k) {
            Swap(a, i, right);
            right--;
        } else {
            i++;
        }
    }
    return i - 1;
}

// 快速排序 - 循环版本
void QuickSort(int a[], int n) {
    // 保存 start, end
    int stack[2 * n];
    int top = 0;  // 栈顶

    // 初始元素入栈
    stack[top++] = 0;
    stack[top++] = n - 1;

    while (top != 0) {
        // 出栈
        int end = stack[--top];
        int start = stack[--top];

        if (start >= end) continue;

        // 分割
        int p = Partition(a, start, end);

        // 左边、右边分别入栈
        stack[top++] = start;
        stack[top++] = p - 1;

        stack[top++] = p + 1;
        stack[top++] = end;
    }
}

int main(void) {
    int n = 9;
    int a[] = {5, 1, 3, 9, 7, 2, 6, 8, 5};
    QuickSort(a, n);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
}
