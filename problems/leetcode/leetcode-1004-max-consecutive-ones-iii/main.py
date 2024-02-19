from typing import List


class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        k0 = 0  # 当前 0 的个数
        ans = 0
        L = R = 0
        while R < len(nums):
            if nums[R] == 0:
                k0 += 1

            # L <= R 而不是 L < R，允许空窗口出现，因为 k 可能是 0
            # 空窗口的时候，答案恰好是 0
            while L <= R and k0 > k:
                if nums[L] == 0:
                    k0 -= 1
                L += 1

            ans = max(ans, R - L + 1)
            R += 1
        return ans
