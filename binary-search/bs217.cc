#include <cassert>
#include <vector>
using namespace std;

int CheckAiEqualsILength(vector<int>& A) {
    auto f = [&](int i) { return A[i] - i; };

    // 找 f(i) >= 1 的左界
    auto find_p = [&]() {
        int l = 0, r = A.size() - 1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (f(m) >= 1)
                r = m;
            else
                l = m + 1;
        }
        return l;
    };

    // 找 f(i) <= -1 的左界
    auto find_q = [&]() {
        int l = 0, r = A.size() - 1;
        while (l < r) {
            int m = (l + r + 1) >> 1;
            if (f(m) <= -1)
                l = m;
            else
                r = m - 1;
        }
        return l;
    };

    return find_p() - find_q() - 1;
}

bool CheckAiEqualsI(vector<int>& A) {
    auto f = [&](int i) { return A[i] - i; };
    int l = 0, r = A.size() - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (f(m) >= 0)
            r = m;
        else
            l = m + 1;
    }
    return A[l] == l;
}

int main(void) {
    vector<int> A1{-3, 0, 1, 3, 4, 6, 7, 8};
    assert(CheckAiEqualsI(A1));
    assert(CheckAiEqualsILength(A1) == 2);

    vector<int> A2{-3, 0, 1, 2, 3, 6, 7, 8};
    assert(!CheckAiEqualsI(A2));

    vector<int> A3{1, 2, 3, 4, 5, 6, 7, 8};
    assert(!CheckAiEqualsI(A3));

    vector<int> A4{-1, 0, 1, 2, 3, 4, 5, 6};
    assert(!CheckAiEqualsI(A4));

    vector<int> A5{-1, 0, 2, 4, 5, 6, 7, 8};
    assert(CheckAiEqualsI(A5));
    assert(CheckAiEqualsILength(A5) == 1);
    return 0;
}
