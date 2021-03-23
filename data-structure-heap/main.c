// 数据结构堆的最小化实现（最小堆）
// https://writings.sh/post/data-structure-heap-and-common-problems

// 采用数组表示堆
//
//           0
//      1         2
//   3     4   5      6
//
// 父亲 i => 左孩子 j1=2*i+1，右孩子 j2=j1+1
// 孩子 j => 父亲 i=(j-1)/2

#include <stdio.h>  // for printf

///////////
// 声明
///////////

void Swap(int a[], int i, int j);  // 交换

void Up(int a[], int j);           // 上浮
void Down(int a[], int n, int i);  // 下沉
void Build(int a[], int n);        // 堆化
int Push(int a[], int n, int v);   // 插入
int Pop(int a[], int n);           // 删除
int Top(int a[]);                  // 堆顶
void Fix(int a[], int i);          // 修整

///////////
// 实现
///////////

// 从位置 j 开始上浮堆
void Up(int a[], int j) {
    while (j > 0) {
        // 父节点
        int i = (j - 1) / 2;
        if (a[i] <= a[j]) break;
        Swap(a, i, j);
        j = i;
    }
}

// 从位置 i 开始下沉大小为 n 的堆
void Down(int a[], int n, int i) {
    while (1) {
        // 左孩子 j1
        int j1 = 2 * i + 1;
        if (j1 >= n) break;

        // 右孩子 j2 （可能不存在）
        int j2 = j1 + 1;

        // j 是其中值更小的孩子
        int j = j1;
        if (j2 < n && a[j2] < a[j1]) j = j2;

        if (a[i] <= a[j]) break;
        Swap(a, i, j);
        i = j;
    }
}

// 将大小为 n 的数组 a 堆化
void Build(int a[], int n) {
    // 从最后一层父节点，不断下沉堆
    for (int i = (n - 1) / 2; i >= 0; i--) {
        Down(a, n, i);
    }
}

// 获取堆顶元素
int Top(int a[]) { return a[0]; }

// 向大小为 n 的堆 a 中添加元素 v
// 返回添加后的数组大小
int Push(int a[], int n, int v) {
    a[n] = v;
    Up(a, n);  // 上浮
    return ++n;
}

// 从大小为 n 的堆 a 中移除堆顶元素
// 返回移除的元素
// 如果堆空，返回 -1
int Pop(int a[], int n) {
    if (n <= 0) return -1;
    n--;
    Swap(a, 0, n);
    Down(a, n, 0);  // 下沉
    return a[n];
}

// Swap 交换数组 a 的位置 i 和 j
void Swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

///////////
// 测试
///////////

int main(void) {
    int n = 6;
    int a[32] = {3, 1, 2, 7, 0, 4};

    // Build heap
    Build(a, n);

    // Push
    n = Push(a, n, 6);

    // Pop and print
    while (n > 0) {
        int v = Pop(a, n--);
        printf("%d ", v);
    }
}
