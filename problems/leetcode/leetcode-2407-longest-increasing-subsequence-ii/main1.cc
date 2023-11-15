#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

class Solution {
   public:
    // 传统 LIS 问题求解
    int traditionalLIS(vector<int>& nums) {
        vector<int> p{nums[0]};
        for (int i = 1; i < nums.size(); i++) {
            if (auto num = nums[i]; num > p.back())
                p.push_back(num);
            else {
                auto j = lower_bound(p.begin(), p.end(), num);
                *j = num;
            }
        }
        return p.size();
    }

    int lengthOfLIS(vector<int>& nums, int k) {
        int n = nums.size();

        // 造一个数组，每一项是 (下标，此下标在 nums 中的数值)
        vector<pair<int, int>> arr;
        for (int i = 0; i < n; i++) arr.push_back({nums[i], i});

        // 按数值排序, 如果相等，则按下标逆序
        sort(arr.begin(), arr.end(), [](const auto& a, const auto& b) {
            return a.first < b.first ||
                   (a.first == b.first && a.second > b.second);
        });

        // 迭代 arr, 找到差值 > k 的地方，切割出来
        // 求解其下标数组的 LIS 问题
        // temp 数组装的是下标
        vector<int> temp;

        int ans = 1;  // 至少为 1

        for (int j = 0; j < n; j++) {
            auto [num, i] = arr[j];

            if ((j >= 1 && num > arr[j - 1].first + k)) {
                // 找到一处断点
                ans = std::max(traditionalLIS(temp), ans);
                // 清空 temp
                temp.clear();
            }
            temp.push_back(i);
        }

        // 残留的部分
        if (!temp.empty()) ans = std::max(traditionalLIS(temp), ans);

        return ans;
    }
};
