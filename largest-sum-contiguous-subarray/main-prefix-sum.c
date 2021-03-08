// 最大连续子序列和问题 - 前缀和方法
// http://writings.sh/post/algorithm-largest-sum-contiguous-subarray

#include <assert.h>
#include <stdio.h>  // for printf

// 返回给定整数数组的最大连续子序列的和。
int LargestSumContiguousSubarray(int nums[], int length) {
    // Sum of 1..j
    int sum = 0;
    // Min value of sum(i), where i < j.
    int min = 0;
    // Max value of delta, where delta = sum(j) - min.
    int max = nums[0];

    for (int j = 0; j < length; j++) {
        sum += nums[j];
        int delta = sum - min;
        if (delta > max) max = delta;
        if (sum < min) min = sum;
    }
    return max;
}

int main(void) {
    int nums1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    assert(LargestSumContiguousSubarray(nums1, 9) == 6);
}
