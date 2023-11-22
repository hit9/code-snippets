#include <cassert>
#include <vector>
using namespace std;

int ClassicBinarySearch(const vector<int>& f, int target) {
    // 先找 >= target 的左界
    int l = 0, r = f.size() - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (f[m] >= target)
            r = m;
        else
            l = m + 1;
    }
    // 再具体判断是否真的等于 target
    if (f[l] == target) return l;
    return -1;  // 找不到
}

int main(void) {
    vector<int> f{1, 2, 3, 4, 5, 5, 7, 8, 10};
    assert(ClassicBinarySearch(f, 2) == 1);
    assert(ClassicBinarySearch(f, 5) == 4);
    assert(ClassicBinarySearch(f, 9) == -1);
    return 0;
}
