#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

// 返回的是 <= 分割点的位置上界
int partition(vector<int>& a, int start, int end) {
    int left = start;
    int right = end;
    int i = start;
    int p = a[start + rand() % (end - start + 1)];
    while (i <= right) {
        if (a[i] < p) {
            std::swap(a[i], a[left]);
            left++;
            i++;
        } else if (a[i] > p) {
            std::swap(a[i], a[right]);
            right--;
        } else
            i++;
    }
    return i - 1;
}

int topk(vector<int>& a, int k, int start, int end) {
    if (start >= end) return a[start];
    int p = partition(a, start, end);
    if (k == p + 1)
        return a[p];
    else if (k < p + 1)
        return topk(a, k, start, p - 1);
    else
        return topk(a, k, p + 1, end);
}

int main(void) {
    int n, k;
    cin >> n >> k;
    getchar();

    vector<int> a(n);
    unordered_set<int> s;

    int c;
    int j = 0;
    for (int i = 0; i < n; i++) {
        cin >> c;
        if (s.find(c) != s.end()) continue;
        s.insert(c);
        a[j++] = c;
    }
    getchar();

    if (k > s.size())
        cout << "NO RESULT" << endl;
    else {
        int ans = topk(a, k, 0, s.size() - 1);
        cout << ans << endl;
    }

    return 0;
}
