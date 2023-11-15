#include <stack>
#include <vector>
using namespace std;
class Solution {
   public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        int left = INT_MAX;
        int right = INT_MIN;

        stack<int> s1;  // 从左向右扫描的递增栈, 存储的是下标
        for (int i = 0; i < n; i++) {
            while (!s1.empty() && nums[s1.top()] > nums[i]) {
                // 追踪逆序情况下，最靠左的位置
                left = std::min(s1.top(), left);
                s1.pop();
            }
            s1.push(i);
        }

        stack<int> s2;  // 从右向左扫描的递减栈, 存储的下标
        for (int i = n - 1; i >= 0; i--) {
            while (!s2.empty() && nums[s2.top()] < nums[i]) {
                // 追踪逆序情况下，最靠左的位置
                right = std::max(s2.top(), right);
                s2.pop();
            }
            s2.push(i);
        }

        // 找不到逆序的
        if (left == INT_MAX || right == INT_MIN) return 0;

        return right - left + 1;
    }
};
