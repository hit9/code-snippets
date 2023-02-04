// 最大连续子序列和问题 - 动态规划方法
// http://writings.sh/post/algorithm-largest-sum-contiguous-subarray

#include <assert.h>
#include <stdio.h>  // for printf

// 返回给定整数数组的最大连续子序列的和。
int LargestSumContiguousSubarray(int nums[], int length) {
    if (length <= 0) return 0;

    int max = 0;
    int dp[length];
    dp[0] = nums[0];

    for (int i = 1; i < length; i++) {
        if (dp[i - 1] > 0)
            dp[i] = dp[i - 1] + nums[i];
        else
            dp[i] = nums[i];

        if (max < dp[i]) max = dp[i];
    }
    return max;
}

int LargestSumContiguousSubarraySpaceO1(int nums[], int length) {
    if (length <= 0) return 0;

    int dp = nums[0];
    int max = dp;

    for (int i = 1; i < length; i++) {
        if (dp > 0)
            dp += nums[i];
        else
            dp = nums[i];

        if (max < dp) max = dp;
    }
    return max;
}

int main(void) {
    int nums1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    assert(LargestSumContiguousSubarraySpaceO1(nums1, 9) == 6);
    return 0;
}
