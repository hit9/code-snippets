#include <iostream>
#include <vector>

using namespace std;

using ull = unsigned long long;

ull Merge(const vector<int>& a, int start1, int end1, const vector<int>& b,
          int start2, int end2, vector<int>& c, int start) {
    ull ans = 0;
    while (start1 <= end1 && start2 <= end2) {
        if (a[start1] <= b[start2])
            c[start++] = a[start1++];
        else {
            c[start++] = b[start2++];
            ans += end1 - start1 + 1;
        }
    }
    while (start1 <= end1) c[start++] = a[start1++];
    while (start2 <= end2) c[start++] = b[start2++];
    return ans;
}

// 归并排序并返回逆序对数量
ull MergeSort(vector<int>& a) {
    int n = a.size();
    ull ans = 0;
    vector<int> tmp(n);
    for (int k = 1; k < n; k *= 2) {
        for (int start = 0; start < n; start += 2 * k) {
            int start1 = start;
            int end1 = std::min(n - 1, start1 + k - 1);
            int start2 = end1 + 1;
            int end2 = std::min(n - 1, start2 + k - 1);
            int end = end2;
            ans += Merge(a, start1, end1, a, start2, end2, tmp, start);
            for (int i = start; i <= end; i++) a[i] = tmp[i];
        }
    }
    return ans;
}

int main(void) {
    int n;
    cin >> n;
    getchar();

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    getchar();

    cout << MergeSort(a) << endl;
    return 0;
}
