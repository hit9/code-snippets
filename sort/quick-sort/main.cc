#include <iostream>
#include <vector>

// 原地分割数组, 返回返回基准值的最右下标
// [   left )  [i]  ( right ]
//    v < p    ^      v > p
// +-----------+
//   v <= p
//
//   分成三份: <p 的部分 [start, left), 等于 p 的部分 [left, i),  大于 p 的部分
//   (right, end).
int partition(std::vector<int>& a, int start, int end) {  // [start, end)
    auto p = a[start];
    int left = start;     // [start, left) 上保持 < p
    int right = end - 1;  // (right, end) 上保持 > p
    int i = left;  // i 是迭代变量, [left, i) 上是已知的 == p 的, 可能为空区间
    while (i <= right) {
        if (a[i] < p) {  // 小于 p 的放左边
            std::swap(a[i], a[left]);
            // i 左侧的都已经检查过, 所以都可以 ++
            left++;
            i++;

        } else if (a[i] > p) {  // 大于 p 的放右边
            std::swap(a[i], a[right]);
            right--;
            // 换过来的 right 目前在 i 位置, i 不能移动，要检查一下这个值
            // 换过去后，right 处已经检查, 所以可以直接 right--
        } else {
            // == p 的时候
            i++;
        }
    }
    return i - 1;
}

void quicksort(std::vector<int>& a, int start, int end) {
    if (start >= end) return;
    auto m = partition(a, start, end);
    quicksort(a, start, m - 1);
    quicksort(a, m + 1, end);
}

int main(void) {
    std::vector<int> a{5, 1, 3, 2, 4, 7, 5, 2, 6};
    quicksort(a, 0, a.size());
    for (auto num : a) {
        std::cout << num << std::endl;
    }
    return 0;
}
