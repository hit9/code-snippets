// https://leetcode.cn/problems/array-of-doubled-pairs
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    bool canReorderDoubled(vector<int>& arr) {
        // 排序
        sort(arr.begin(), arr.end());
        // 制作 map
        unordered_map<int, int> d;
        for (auto x : arr) d[x]++;
        // 判断
        for (int i = 0; i < arr.size(); i++) {
            auto x = arr[i];
            if (d[x] == 0) continue;

            if (x >= 0 && d[2 * x] == 0) {
                return false;
            } else {
                d[2 * x]--;
            }
            if (x < 0 && (x & 1)) return false;  // 不可以奇数
            if (x < 0 && d[x / 2] == 0) {
                return false;
            } else {
                d[x / 2]--;
            }
            d[x]--;
        }
        return true;
    }
};
