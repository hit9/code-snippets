// 回溯递归思路
#include <vector>
using namespace std;
class Solution {
   public:
    vector<int> chosen;
    vector<vector<int>> ans;

    // dfs 完成子问题 a[k..N] 上的答案
    void dfs(vector<int>& a, int k) {
        // 把 chosen 看做左右两部分:
        //
        //           {A}                              {B}
        // { 已选择的 a[0..k-1] 部分}  k  .... { i  i+1  ..... N}
        //                                          ------------
        //                                       i+ dfs(a[i+1..N])
        //
        //  A 部分是,不考虑任何 [k..N] 的答案
        //  B 部分是,至少考虑 a[k..N] 上一个元素的答案
        //    依次考虑, 每个必包含 a[i] 的组合
        //    也就是, 选中 a[i] + 子问题 dfs(a[i+1..N])
        //
        //  二者结合 都要, 即枚举了所有的组合

        // 不考虑 a[k..N] 内的任何元素, 即直接收集已有答案
        ans.push_back(chosen);

        for (int i = k; i < a.size(); i++) {
            chosen.push_back(a[i]);  // 考虑必包含 a[i] 的所有组合
            dfs(a, i + 1);           // 子问题 a[i+1..N], 缩小了规模
            chosen.pop_back();       // 撤销, 以继续下一个可能
        }
    }

    vector<vector<int>> subsets(vector<int>& a) {
        dfs(a, 0);
        return ans;
    }
};
