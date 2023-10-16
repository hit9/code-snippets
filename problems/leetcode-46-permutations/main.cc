// https://leetcode.cn/problems/permutations/description/?envType=study-plan-v2&envId=top-100-liked
// 46. 全排列
// 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
//
// 示例 1： 输入：nums = [1,2,3] 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
//
// 示例 2： 输入：nums = [0,1] 输出：[[0,1],[1,0]]
//
// 示例 3： 输入：nums = [1] 输出：[[1]]


#include <vector>

using namespace std;

class Solution {
   public:
    // x 是要固定第几位
    // d 来收集方案
    void dfs(vector<int>& nums, int x, vector<vector<int>>& d) {
        if (x == nums.size() - 1) {  // 已固定完所有位
            // 拷贝到结果中
            d.push_back(nums);
            return;
        }

        for (int i = x; i < nums.size(); i++) {
            std::swap(nums[i], nums[x]);  // 将 nums[i] 固定在第 x 位上
            dfs(nums, x + 1, d);          // 继续固定下一位
            std::swap(nums[i], nums[x]);  // 回溯, 还原回来
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> d;
        dfs(nums, 0, d);
        return d;
    }
};

int main(void) { return 0; }
