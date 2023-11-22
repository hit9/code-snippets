#include <cassert>
#include <vector>
using namespace std;

int FindFirst1(const vector<int>& f) {
    int l = 0;
    int r = f.size() - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (f[m] == 1)
            r = m;
        else
            l = m + 1;
    }
    return l;
}

int main(void) {
    vector<int> f1{0, 0, 0, 0, 0, 0, 1, 1};
    assert(FindFirst1(f1) == 6);
    vector<int> f2{0, 0, 0, 0, 0, 0, 1, 1, 1};
    assert(FindFirst1(f2) == 6);
    vector<int> f3{1, 1, 1};
    assert(FindFirst1(f3) == 0);
    vector<int> f4{0, 0, 0};
    assert(FindFirst1(f4) == 2);  // 无法识别「不存在」
    return 0;
}
