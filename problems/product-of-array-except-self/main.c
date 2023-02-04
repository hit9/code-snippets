// 除自身以外数组的乘积
// https://leetcode.cn/problems/product-of-array-except-self/

#include <stdio.h>  // for printf

// 输入大小为 n 的数组 nums，ProductExceptSelf 保证 results 数组的
// 第 i 项等于 nums 数组中除去 nums[i] 之外的其余元素的乘积
// 限制：不允许使用除法，且在 O(n) 时间复杂度、O(1) 空间复杂度内完成
// 数组 results 的大小已保证是 n.
void ProductExceptSelf(int nums[], int n, int results[]) {
    // 初始化 results
    for (int i = 0; i < n; i++) results[i] = 1;

    // 记录从最左到当前项 (不含当前项) 的累乘结果
    int left = 1;
    // 记录从最右到当前项 (不含当前项) 的累乘结果
    int right = 1;

    for (int i = 0; i < n; i++) {
        int j = n - 1 - i;

        results[i] *= left;
        results[j] *= right;

        left *= nums[i];
        right *= nums[j];
    }
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int n = 4;
    int results[4];

    ProductExceptSelf(nums, n, results);

    for (int i = 0; i < n; i++) printf("%d ", results[i]);
    return 0;
}
