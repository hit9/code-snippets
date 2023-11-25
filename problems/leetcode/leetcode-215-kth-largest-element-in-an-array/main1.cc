// 快速选择
// https://leetcode.cn/problems/kth-largest-element-in-an-array
// 目前这个快速选择的方法，leetcode 有个用例会超时

#include <cstdlib>
#include <vector>

using namespace std;

class Solution {
   public:
    // 分成三份, 左边大于 p, 中间等于 p, 右侧小于 p
    int partition(vector<int>& nums, int start, int end) {
        int p = nums[start + (rand() % (end - start + 1))];
        int left = start;
        int right = end;
        int i = start;

        while (i <= right) {
            if (nums[i] > p) {
                std::swap(nums[i], nums[left]);
                left++;
                i++;
            } else if (nums[i] < p) {
                std::swap(nums[i], nums[right]);
                right--;
            } else
                i++;
        }
        // 返回 >= 选择元素的右界位置
        return i - 1;
    }

    int topk(vector<int>& nums, int start, int end, int k) {
        if (end <= start) return nums[k - 1];
        int p = partition(nums, start, end);
        if (p + 1 >
            k)  // 左边 (包括 p) 有 p+1 个元素，如果多于 k 个, 继续向左侧寻找
            return topk(nums, start, p - 1, k);
        else if (p + 1 < k)  // 如果不足 k 个, 向右侧继续寻找
            return topk(nums, p + 1, end, k);
        else  // 如果恰好 k 个
            return nums[p];
    }

    int findKthLargest(vector<int>& nums, int k) {
        return topk(nums, 0, nums.size() - 1, k);
    }
};
