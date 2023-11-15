#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 输出一个数组的一个最长递增子序列
// 时间复杂度 O(nlogn)
// 空间复杂度: O(n^2)

class Solution {
   public:
    vector<int> findOneLIS(vector<int>& nums) {
        using Node = pair<int, int>;  // 槽位, {父节点在桶中的位置、元素值}
        using Bucket = vector<Node>;  // 桶

        vector<Bucket> buckets;  // 各个列的桶
        vector<int> p;           // 辅助数组, 冗余各个桶的尾部元素

        // 放入头节点到第一个桶
        buckets.push_back({{-1, nums[0]}});
        p.push_back(nums[0]);

        // 辅助函数, 给第 k 个桶放入一个新元素
        auto push = [&](int k, int num) {
            // 上个桶的当前尾部节点当做父节点
            int j = (k == 0) ? -1 : (buckets[k - 1].size() - 1);
            buckets[k].push_back({j, num});
            // 更新辅助数组
            p[k] = num;
        };

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > p[p.size() - 1]) {
                // 新建一个空桶, 扩展辅助数组
                buckets.push_back({});
                p.push_back(0);

                // 加入此元素到新桶 (最后一个桶)
                push(buckets.size() - 1, nums[i]);
            } else {
                // 查找合适的桶放入新元素
                int k = lower_bound(p.begin(), p.end(), nums[i]) - p.begin();
                push(k, nums[i]);
            }
        }

        // 要返回最长的上升子序列，需要从最后一个桶反向找回去
        vector<int> ans(buckets.size());

        // i 是第 i 个桶，j 父节点在前面一个桶的位置
        for (int i = buckets.size() - 1, j = -1; i >= 0; i--) {
            auto& b = buckets[i];
            auto& [j1, num] = b[j < 0 ? (b.size() - 1) : j];
            j = j1;
            ans[i] = num;
        }

        return ans;
    }
};

int main(void) {
    Solution solution;

    // 测试 1
    vector<int> nums1{4, 2, 7, 6, 8, 3, 5, 6};
    auto ans1 = solution.findOneLIS(nums1);
    for (auto x : ans1) cout << x << " ";
    cout << endl;

    // 测试 2
    vector<int> nums2{8, 10, 2, 9, 6, 13, 1, 9, 5, 12, 3, 10, 16};
    auto ans2 = solution.findOneLIS(nums2);
    for (auto x : ans2) cout << x << " ";
    cout << endl;

    // 测试 3
    vector<int> nums3{9, 8, 7, 6, 5, 4, 3, 2, 1};
    auto ans3 = solution.findOneLIS(nums3);
    for (auto x : ans3) cout << x << " ";
    cout << endl;

    // 测试 4
    vector<int> nums4{1, 2, 3, 4, 5, 6, 7, 8};
    auto ans4 = solution.findOneLIS(nums4);
    for (auto x : ans4) cout << x << " ";
    cout << endl;

    // 测试 5
    vector<int> nums5{4,  0,  7,  3, 5,  14, 9,  5, 12, 13,
                      18, 21, 16, 7, 20, 31, 29, 2, 9};
    auto ans5 = solution.findOneLIS(nums5);
    for (auto x : ans5) cout << x << " ";
    cout << endl;

    // 测试 6
    vector<int> nums6{8, 10, 2, 9, 6, 13, 1, 9, 5, 12, 3, 10, 7, 9, 11};
    auto ans6 = solution.findOneLIS(nums6);
    for (auto x : ans6) cout << x << " ";
    cout << endl;
}
