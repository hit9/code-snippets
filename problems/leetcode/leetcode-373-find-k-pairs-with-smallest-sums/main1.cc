#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
    using ull = unsigned long long;
    using ll = long long;
    using P = pair<int, int>;

   public:
    // 找到两个数组中数对和不超过给定值的数对的数量
    // 等效于下面的 findPairs，但是只是计数
    ull count(const vector<int>& a, const vector<int>& b, ll val) {
        ull ans = 0;
        // 对 a 中的每一项 x 来说，相当于找 b 中 <= val-x 的右界的问题
        for (auto x : a) {
            int target = val - x;
            // 注意防止全部太大的情况, 此时找不到右界
            if (!(b[0] > target)) {
                int l = 0;
                int r = b.size() - 1;
                while (l < r) {
                    int m = (l + r + 1) >> 1;
                    if (b[m] <= target)
                        l = m;
                    else
                        r = m - 1;
                }
                ans += (ull)l + 1;
            }
        }
        return ans;
    }

    // 找到两个数组中数对和不超过给定值的数对
    // 并按照从小到大的顺序输出
    // 最多 k 个
    void findPairs(const vector<int>& a, const vector<int>& b, ll val, int k,
                   vector<vector<int>>& ans) {
        // 大顶堆
        auto cmp = [&](const P& a, const P& b) {
            return a.first + a.second < b.first + b.second;
        };
        priority_queue<P, vector<P>, decltype(cmp)> q(cmp);

        // 对 a 中的每一项 x 来说，相当于找 b 中 <= val-x 的右界的问题
        for (auto x : a) {
            int target = val - x;
            // 注意防止全部太大的情况, 此时找不到右界
            if (!(b[0] > target)) {
                int l = 0;
                int r = b.size() - 1;
                while (l < r) {
                    int m = (l + r + 1) >> 1;
                    if (b[m] <= target)
                        l = m;
                    else
                        r = m - 1;
                }
                // 收集起来
                for (int j = 0; j <= l; j++) {
                    q.push({x, b[j]});
                    // 如果数量超过 k 了，置换出最大的
                    if (q.size() >= k + 1) q.pop();
                }
            }
        }
        // 取出堆中的元素
        while (!q.empty()) {
            auto [a, b] = q.top();
            ans.push_back({a, b});
            q.pop();
        }
        // 反转一下
        reverse(ans.begin(), ans.end());
    }

    vector<vector<int>> kSmallestPairs(vector<int>& a, vector<int>& b, int k) {
        vector<vector<int>> ans;

        // 先二分判定找到符合条件的第 k 小的和
        ll l = a[0] + b[0];
        ll r = a[a.size() - 1] + b[b.size() - 1];

        // 相当于找满足 count(mid) >= k 的下界
        while (l < r) {
            int m = (l + r) >> 1;
            if (count(a, b, m) >= k)
                r = m;
            else
                l = m + 1;
        }

        // 然后收集这些数对
        findPairs(a, b, l, k, ans);
        return ans;
    }
};

int main(void) {
    Solution s;
    vector<int> a{1, 2};
    vector<int> b{3};
    for (const auto& item : s.kSmallestPairs(a, b, 3))
        cout << item[0] << "," << item[1] << endl;
    return 0;
}
