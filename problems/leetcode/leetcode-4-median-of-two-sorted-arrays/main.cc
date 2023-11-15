// https://leetcode.cn/problems/median-of-two-sorted-arrays/description/
// 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和
// nums2。请你找出并返回这两个正序数组的 中位数 。 算法的时间复杂度应该为 O(log
// (m+n)) 。
//
// 示例 1： 输入：nums1 = [1,3], nums2 = [2] 输出：2.00000
// 解释：合并数组 = [1,2,3] ，中位数 2
//
// 示例 2： 输入：nums1 = [1,2], nums2 =
// [3,4] 输出：2.50000 解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        // 假设第一个数组的长度更短
        if (m < n) return findMedianSortedArrays(nums2, nums1);

        // 提前向数组插入 '#'
        // 比如 [1,2,3]
        // 变成 [#,1,#,2,#,3,#]
        // 假如原来数组个数是n, 插入后个数是 2n+1
        // 所以总的个数一定是 2(m+n+1), 是一个偶数

        int N = 2 * n + 1;  // 新的长度
        int M = 2 * m + 1;  // 新的长度

        // C1 是第一个数组的分割点、C2 是第二个数组的分割点
        int C1, C2;

        // [ L1 ] C1 [ R1 ]       数组1 在位置 C1 分割为两部分
        // [ L2 ] C2 [ R2 ]       数组2 在位置 C2 分割为两部分

        int LMax1;  // 第一个数组 C1 左侧的元素的值，一定是 L1 中的最大值
        int LMax2;  // 第二个数组 C2 左侧的元素的值，一定是 L2 中的最大值
        int RMin1;  // 第一个数组 C1 右侧的元素的值，一定是 R1 中的最小值
        int RMin2;  // 第二个数组 C2 右侧的元素的值，一定是 R2 中的最小值

        // 总的思路是:
        // 1. 分割的左侧 L1 和 L2 的总个数总是一半多 K = m+n+1
        //    所以分割点的和一定是 C1+C2 = K-1 (可以极限考虑，取C1=0, C2=是 K-1
        //    才可以有 K 个元素)
        // 2. 要想找到中位数, 必须 L1 和 L2 的数都小于 R1 和 R2 中的数，
        //    也就是要求: LMax1 <= RMin2 且 LMax2 <= RMin1
        // 3. 如果分割后，LMax1 > RMin2 说明 L1 部分的元素过多，C1 要向左移
        //    同理，如果 LMax2 > RMin1 说明 L2 部分的元素过多，C2 要向左移,
        //    也就是 C1 右移
        // 4. LMaxi = (Ci-1)/2 位置上的元素 RMini = Ci/2 位置上的元素
        //    这一点可以演算一下:
        //    # 0 # 1 # 2 # 3 # 4 #
        //    0 1 2 3 4 5 6 7 8 9 10
        //    扩展后的坐标是 Ci

        int L = 0;      // C1 分割的左界
        int R = N - 1;  // C1 分割的右界

        int K = m + n + 1;

        while (L <= R) {
            C1 = (L + R) / 2;  // 二分取中间位置
            C2 = K - 1 - C1;

            LMax1 = (C1 == 0) ? INT_MIN : nums1[(C1 - 1) / 2];
            LMax2 = (C2 == 0) ? INT_MIN : nums2[(C2 - 1) / 2];
            RMin1 = (C1 == N - 1) ? INT_MAX : nums1[C1 / 2];
            RMin2 = (C2 == M - 1) ? INT_MAX : nums2[C2 / 2];

            if (LMax1 > RMin2)
                R = C1 - 1;
            else if (LMax2 > RMin1)
                L = C1 + 1;
            else
                break;
        }
        // 总数偶数的情况下，左侧和右侧不重叠
        // 总数奇数的情况下，左侧和右侧在中间元素处重叠
        // 所以 max(LMax1, LMax2) 和 min(RMin1, RMin2) 一定可以决定中位数
        return (std::max(LMax1, LMax2) + std::min(RMin1, RMin2)) / 2.0;
    }
};

int main(void) {
    Solution solution;
    vector<int> nums1{1, 3, 5};
    vector<int> nums2{2, 4};
    cout << solution.findMedianSortedArrays(nums1, nums2) << endl;  // 3.0
    return 0;
}
