#include <vector>
using namespace std;
class Solution {
   public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        // 求严格大于的，那么 z 一定不可以
        if (target == 'z') return letters[0];

        // 找严格大于 target 的
        // 就是找 >= target+1 的
        target += 1;

        int l = 0, r = letters.size();
        while (l < r) {
            int m = (l + r) >> 1;
            if (letters[m] < target)
                l = m + 1;
            else
                r = m;
        }

        if (l >= letters.size()) return letters[0];
        return letters[l];
    }
};
