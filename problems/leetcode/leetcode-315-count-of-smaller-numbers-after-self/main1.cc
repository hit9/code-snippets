// https://leetcode.cn/problems/count-of-smaller-numbers-after-self/description/

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// 归并排序做法
// 从大到小排序

class Solution {
    using P = pair<int, int>;  // id, value
   public:
    void merge(vector<P>& a, int start1, int end1, int start2, int end2,
               vector<P>& tmp, int start, vector<int>& cnt) {
        while (start1 <= end1 && start2 <= end2) {
            if (a[start1].second > a[start2].second) {
                cnt[a[start1].first] += end2 - start2 + 1;
                tmp[start++] = a[start1++];
            } else {
                tmp[start++] = a[start2++];
            }
        }
        while (start1 <= end1) tmp[start++] = a[start1++];
        while (start2 <= end2) tmp[start++] = a[start2++];
    }

    void mergeSort(vector<P>& a, vector<int>& cnt) {
        int n = a.size();
        vector<P> tmp(n);

        for (int k = 1; k < n; k *= 2) {
            for (int start = 0; start < n; start += 2 * k) {
                int start1 = start;
                int end1 = min(n - 1, start + k - 1);
                int start2 = end1 + 1;
                int end2 = min(n - 1, start2 + k - 1);
                // TODO end 超过 n?
                merge(a, start1, end1, start2, end2, tmp, start, cnt);
                // 复制回 a
                for (int i = start; i <= end2; i++) a[i] = tmp[i];
            }
        }
    }

    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<P> a(n);
        for (int i = 0; i < n; i++) a[i] = {i, nums[i]};
        vector<int> cnt(n, 0);
        mergeSort(a, cnt);
        return cnt;
    }
};

int main(void) {
    vector<int> nums{5, 2, 6, 1};
    Solution s;
    auto result = s.countSmaller(nums);
    for (int i = 0; i < result.size(); i++) cout << result[i] << " ";
    cout << endl;
    return 0;
}
