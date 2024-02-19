from typing import List


class Solution:
    def maxScore(self, a: List[int], k: int) -> int:
        k1 = len(a) - k
        S = sum(a)
        min_s = S
        s = 0

        L = R = 0
        while R < len(a):
            s += a[R]
            while R - L + 1 > k1:
                s -= a[L]
                L += 1
            if R - L + 1 == k1:
                if min_s > s:
                    min_s = s
            R+=1
        return S - min_s
