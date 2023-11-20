#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
class Solution {
   public:
    using P = pair<int, int>;

    // 计算两个有序数组的前 k 个数对和的数组
    // 返回的数组的大小是 k
    // 且要求 k <= size(a) * size(b)
    vector<int> mergeTwo(const vector<int>& a, const vector<int>& b, int k) {
        auto cmp = [&](const P& x, const P& y) {
            return a[x.first] + b[x.second] > a[y.first] + b[y.second];
        };

        // 小顶堆，维护的是 n 个最小的 a[i] + b[j] 的下标 (i, j)
        priority_queue<P, vector<P>, decltype(cmp)> q(cmp);

        // a[i], b[0] 入队
        for (int i = 0; i < a.size(); i++) q.push({i, 0});

        vector<int> ans;

        // 置换 k 次，获取到前 k 个最小的数对的和
        while (k-- && !q.empty()) {
            auto [i, j] = q.top();
            q.pop();
            ans.push_back(a[i] + b[j]);
            if (j + 1 < b.size()) q.push({i, j + 1});
        }
        return ans;
    }

    int kthSmallest(vector<vector<int>>& mat, int k) {
        int m = mat.size();
        vector<int> ans = mat[0];
        for (int i = 1; i < m; i++) {
            ans = mergeTwo(mat[i], ans, k);
        }
        return ans.back();
    }
};

int main(void) {
    vector<vector<int>> mat{{1, 10, 10}, {1, 4, 5}, {2, 3, 6}};
    Solution s;
    cout << s.kthSmallest(mat, 14) << endl;
    return 0;
}
