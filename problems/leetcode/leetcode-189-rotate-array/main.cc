#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 思路如下：
//
//     首先对整个数组实行翻转，这样子原数组中需要翻转的子数组，就会跑到数组最前面。
//     这时候，从 kkk 处分隔数组，左右两数组，各自进行翻转即可。

class Solution {
   public:
    void rotate(vector<int>& a, int k) {
        k %= a.size();
        reverse(a.begin(), a.end());
        reverse(a.begin(), a.begin() + k);
        reverse(a.begin() + k, a.end());
    }
};

int main(void) {
    vector<int> nums{0, 1, 2, 3, 4, 5, 6};
    Solution s;
    s.rotate(nums, 3);
    return 0;
}
