#include <unordered_map>
using namespace std;
using ull = unsigned long long;
class Solution {
   public:
    bool judgeSquareSum(int c) {
        unordered_map<int, ull> d1;
        unordered_map<ull, int> d2;
        int k = 0;
        while (1) {
            ull s = (ull)k * k;
            if (s > c) break;
            d1[k] = s;
            d2[s] = k;
            k++;
        }

        for (int i = 0; i < k; i++) {
            if (d2.find(c - d1[i]) != d2.end()) return true;
        }
        return false;
    }
};
