#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> majorityElement(vector<int>& nums) {
        // 两个候选者 a 和 b， 手里各自有 va 和 vb 张票
        // 例如 A B A B C B C D B
        // 模拟下投票过程:
        //    前面两列是候选人，第三列是抵消者 , X 是抵消记号
        //
        //    第 N 轮情况      输入      说明
        //    A                A         第 1 个候选人空缺，选择为 A
        //
        //    A B              B         第 2 个候选人空缺，选择为 B
        //
        //    A B              A         候选人 A 票数+1
        //    A
        //
        //    A B              B         候选人 B 票数+1
        //    A B
        //
        //    X X X            C         抵消一次
        //    A B
        //
        //    X X X            B         候选人 B 票数+1
        //    A B
        //      B
        //
        //    X X X            C         再抵消一次
        //    X X X
        //      B
        //
        //    X X X            D         第一个候选人空缺，选用 D
        //    X X X
        //    D B
        //
        //    X X X
        //    X X X            B         候选人 B 票数+1
        //    D B
        //      B
        //
        // 可以看到
        //  1. 最终的候选者并不一定是要找的众数，比如 D
        //  2. 但是消掉的数字一定不是要找的众数.
        //     因为被消的任一行 X 表示的数字互不相同, 一个数字在所有 X
        //     矩阵中出现的次数最多是
        //     在每个行只出现一次的情况。而被消掉的行数不超过 n/3.
        //
        //  最终我们只需要再次检查下最终剩余的两个候选人，确定其是否真正为要找的众数
        //
        int a, b;
        int va = 0, vb = 0;

        for (auto v : nums) {
            if (va > 0 && v == a)  // va > 0 的检查: 确保 a 仍然是合法的候选人
                va++;
            else if (vb > 0 && v == b)
                vb++;
            else if (va == 0) {
                a = v;
                va = 1;
            } else if (vb == 0) {
                b = v;
                vb = 1;
            } else {
                va--;
                vb--;
            }
        }

        // 检查
        vector<int> ans;
        int na = 0, nb = 0;
        for (auto v : nums) {
            if (v == a) na++;
            if (v == b) nb++;
        }

        if (va > 0 && na > nums.size() / 3) ans.push_back(a);
        if (vb > 0 && nb > nums.size() / 3) ans.push_back(b);
        return ans;
    }
};
