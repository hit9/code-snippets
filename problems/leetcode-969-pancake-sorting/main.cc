// https://leetcode.cn/problems/pancake-sorting
// 969. 煎饼排序
// 给你一个整数数组 arr ，请使用 煎饼翻转 完成对数组的排序。
// 一次煎饼翻转的执行过程如下： 选择一个整数 k ，1 <= k <= arr.length 反转子数组
// arr[0...k-1]（下标从 0 开始） 例如，arr = [3,2,1,4] ，选择 k = 3
// 进行一次煎饼翻转，反转子数组 [3,2,1] ，得到 arr = [1,2,3,4] 。
// 以数组形式返回能使 arr 有序的煎饼翻转操作所对应的 k
// 值序列。任何将数组排序且翻转次数在 10 * arr.length
// 范围内的有效答案都将被判断为正确。

#include <algorithm>
#include <vector>
using namespace std;
class Solution {
   public:
    vector<int> pancakeSort(vector<int>& arr) {
        vector<int> ans;
        auto rev = [&](int k) {
            std::reverse(arr.begin(), arr.begin() + k);
            ans.push_back(k);
        };

        vector<int> x = arr;  // copy
        sort(x.begin(), x.end());

        int j = x.size() - 1;

        // n > 1 的注释: 只有一个元素的时候，已经没必要再排序了
        int n = arr.size();

        while (n > 1) {
            // 跳过有序部分
            if (arr[n - 1] == x[j]) {
                n--;
                j--;
                continue;
            };

            // 找 max 的位置 k
            int k = 0;
            int m = x[j--];  // max

            for (int i = n - 1; i >= 0; i--) {
                if (arr[i] == m) {
                    k = i;
                    break;
                }
            }

            if (k != n - 1) {
                // 翻到前面作为第0个元素
                if (k >= 1) rev(k + 1);
                // 反转整个数组
                rev(n);
            }

            n--;
        }
        return ans;
    }
};
