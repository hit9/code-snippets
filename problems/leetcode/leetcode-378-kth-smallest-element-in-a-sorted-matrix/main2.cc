#include <algorithm>
#include <vector>
using namespace std;

class Solution {
   public:
    // 归并两个有序数组, 取其前 top(min(k, n)) 元素
    vector<int> mergeTwo(const vector<int>& a, const vector<int>& b, int k) {
        vector<int> ans;

        int i = 0, j = 0;

        while (i < a.size() && j < b.size() && k) {
            if (a[i] <= b[j])
                ans.push_back(a[i++]);
            else
                ans.push_back(b[j++]);
            k--;
        }
        while (i < a.size() && k) {
            ans.push_back(a[i++]);
            k--;
        }
        while (j < b.size() && k) {
            ans.push_back(b[j++]);
            k--;
        }
        return ans;
    }

    // 分治归并
    vector<int> merge(const vector<vector<int>>& mat, int k) {
        int m = mat.size();
        if (m == 1) return mat[0];
        if (m == 2) return mergeTwo(mat[0], mat[1], k);

        // 分成上下两半矩阵
        vector<vector<int>> mat1;
        int i = 0;
        for (; i < m / 2; i++) mat1.push_back(mat[i]);

        vector<vector<int>> mat2;
        for (; i < m; i++) mat2.push_back(mat[i]);

        // 向上归并
        return mergeTwo(merge(mat1, k), merge(mat2, k), k);
    }

    int kthSmallest(vector<vector<int>>& matrix, int k) {
        auto ans = merge(matrix, k);
        return ans[k - 1];
    }
};
