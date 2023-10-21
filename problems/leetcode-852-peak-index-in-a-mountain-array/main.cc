// 山脉数组的峰顶索引
// https://leetcode.cn/problems/peak-index-in-a-mountain-array
#include <vector>
using namespace std;
class Solution {
   public:
    // 求峰值
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size();
        int L = 0;
        int R = n - 1;
        while (L <= R) {
            int M = (L + R) / 2;
            // 题目说了 0 < i < arr.length - 1
            if (M == 0)
                L = 1;
            else if (M == n - 1)
                R = n - 2;
            else if (arr[M - 1] < arr[M] && arr[M] > arr[M + 1])
                return M;
            else if (arr[M - 1] < arr[M] && arr[M] < arr[M + 1])
                L = M + 1;
            else
                R = M - 1;
        }
        return 0;
    }
};
