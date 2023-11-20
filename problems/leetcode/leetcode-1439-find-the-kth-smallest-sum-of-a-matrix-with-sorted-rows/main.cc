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
    // a 和 b 的大小一样要确保是 n
    // 且要求 k <= n^2
    vector<int> _mergeTwo(const vector<int>& a, const vector<int>& b, int k) {
        int n = a.size();

        auto cmp = [&](const P& x, const P& y) {
            return a[x.first] + b[x.second] > a[y.first] + b[y.second];
        };

        // 小顶堆，维护的是 N 个最小的 a[i] + b[j] 的下标 (i, j)
        priority_queue<P, vector<P>, decltype(cmp)> q(cmp);

        // a[i], b[0] 入队
        for (int i = 0; i < n; i++) q.push({i, 0});

        vector<int> ans;

        // 置换 k 次，获取到前 k 个最小的数对的和
        while (k--) {
            auto [i, j] = q.top();
            q.pop();
            ans.push_back(a[i] + b[j]);
            q.push({i, j + 1});
        }
        return ans;
    }

    // depth 是递归深度, 从 0 开始
    // 细节：只要不是最后一次合并操作，只需要取前 int c = min(n,k) 个就可以
    vector<int> mergeTwo(const vector<int>& a, const vector<int>& b, int k,
                         int c, int depth) {
        if (depth != 0) return _mergeTwo(a, b, c);
        return _mergeTwo(a, b, k);
    }

    vector<int> merge(vector<vector<int>>& mat, int k, int c, int depth) {
        int m = mat.size();
        if (m == 1) return mat[0];
        if (m == 2) return mergeTwo(mat[0], mat[1], k, c, depth);

        // 分成上下两半矩阵
        vector<vector<int>> mat1;
        int i = 0;
        for (; i < m / 2; i++) mat1.push_back(mat[i]);

        vector<vector<int>> mat2;
        for (; i < m; i++) mat2.push_back(mat[i]);

        // 向上归并
        return mergeTwo(merge(mat1, k, c, depth + 1),
                        merge(mat2, k, c, depth + 1), k, c, depth);
    }

    int kthSmallest(vector<vector<int>>& mat, int k) {
        int n = mat[0].size();
        // 采用归并，分治两两合并
        // c 是中间向上归并时，每行需要保留的大小
        int c = std::min(n, k);
        auto ans = merge(mat, k, c, 0);
        return ans[k - 1];
    }
};

int main(void) {
    vector<vector<int>> mat{{1, 10, 10}, {1, 4, 5}, {2, 3, 6}};
    Solution s;
    cout << s.kthSmallest(mat, 7) << endl;
    return 0;
}
