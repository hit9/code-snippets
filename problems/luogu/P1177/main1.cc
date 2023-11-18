// C++ 版本 循环版本归并排序
#include <iostream>
#include <vector>

using namespace std;

// 合并有序数组 a 和 b 的两个 range 到 c 的 start3 位置
void Merge(const vector<int>& a, int start1, int end1, const vector<int>& b,
           int start2, int end2, vector<int>& c, int start) {
    while (start1 <= end1 && start2 <= end2) {
        if (a[start1] <= b[start2])
            c[start++] = a[start1++];
        else
            c[start++] = b[start2++];
    }
    while (start1 <= end1) c[start++] = a[start1++];
    while (start2 <= end2) c[start++] = b[start2++];
}

void MergeSort(vector<int>& a) {
    int n = a.size();
    vector<int> tmp(n, 0);

    // 每 k 个元素一归并, 不断翻倍 k
    //
    // [   k 个  ]   +  [   k 个   ]
    // start         |
    // start1   end1 | start2   end2
    //
    for (int k = 1; k < n; k *= 2) {
        for (int start = 0; start < n; start += 2 * k) {
            int start1 = start;
            int end1 = std::min(start1 + k - 1, n - 1);  // 不要越界
                                                         //
            int start2 = end1 + 1;
            int end2 = std::min(start2 + k - 1, n - 1);  // 不要越界

            int end = end2;

            // 合并
            Merge(a, start1, end1, a, start2, end2, tmp, start);

            // 拷贝到原数组
            for (int i = start; i <= end; i++) a[i] = tmp[i];
        }
    }
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
