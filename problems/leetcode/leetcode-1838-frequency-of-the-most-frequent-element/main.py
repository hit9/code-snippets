from typing import List


class Solution:
    def maxFrequency(self, a: List[int], k: int) -> int:
        a.sort()
        s = 0  # 窗口内的实际的区间和
        ans = 0
        L = R = 0
        while R < len(a):
            s += a[R]
            while L < R and a[R] * (R - L + 1) > k + s:
                s -= a[L]
                L += 1
            ans = max(ans, R - L + 1)
            R += 1
        return ans
