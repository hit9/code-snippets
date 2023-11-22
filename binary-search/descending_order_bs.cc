#include <cassert>
#include <vector>
using namespace std;

int DescendingLeftBound(const vector<int>& f, int target) {
    // 求 f(m) <= target 的左界
    // 等价于求 INF - f(m) >= INF - target 的左界
    auto g = [&](int m) { return INT_MAX - f[m]; };
    // g 是升序的
    int l = 0, r = f.size() - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (g(m) >= INT_MAX - target)
            r = m;
        else
            l = m + 1;
    }
    return l;
}

int main(void) {
    vector<int> f{19, 10, 9, 9, 5, 4, 2};
    assert(DescendingLeftBound(f, 9) == 2);
    assert(DescendingLeftBound(f, 5) == 4);
    return 0;
}
