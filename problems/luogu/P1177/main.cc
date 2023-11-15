// 排序
// https://www.luogu.com.cn/problem/P1177

#include <iostream>
#include <vector>

// 合并两个有序数组 a 和 b 的一部分到第三个数组 c
void _MergeTwoSortedArrays(const std::vector<int>& a, int start1, int end1,
                           const std::vector<int>& b, int start2, int end2,
                           std::vector<int>& c, int start3) {
    int i = start1;
    int j = start2;
    int k = start3;
    while (i <= end1 && j <= end2) {
        if (a[i] <= b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    }
    while (i <= end1) c[k++] = a[i++];
    while (j <= end2) c[k++] = b[j++];
}

// 递归合并过程
void _MergeSort(std::vector<int>& a, std::vector<int>& tmp, int start,
                int end) {
    if (start >= end) return;

    int start1 = start;
    int end1 = (start + end) >> 1;

    int start2 = end1 + 1;
    int end2 = end;

    _MergeSort(a, tmp, start1, end1);
    _MergeSort(a, tmp, start2, end2);

    // 合并到 tmp
    _MergeTwoSortedArrays(a, start1, end1, a, start2, end2, tmp, start);

    // 拷贝 tmp 到 a
    for (int i = start; i <= end; i++) a[i] = tmp[i];
}

void MergeSort(std::vector<int>& a) {
    std::vector<int> tmp(a.size());
    _MergeSort(a, tmp, 0, a.size() - 1);
}

int main(void) {
    int n;
    std::cin >> n;
    std::getchar();

    std::vector<int> a(n, 0);
    for (int i = 0; i < n; i++) std::cin >> a[i];
    std::getchar();

    MergeSort(a);

    for (int i = 0; i < n; i++) std::cout << a[i] << " ";
    std::cout << std::endl;

    return 0;
}
