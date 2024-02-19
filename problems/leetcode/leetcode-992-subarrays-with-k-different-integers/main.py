from collections import defaultdict
from typing import List


class Solution:
    def subarraysWithKDistinct(self, a: List[int], k: int) -> int:
        # 窗口1: <= k, 窗口2: <k
        # 两个窗口之间的个数即是答案
        d1, d2 = defaultdict(int), defaultdict(int)
        c1 = c2 = ans = 0
        L1 = L2 = R = 0
        while R < len(a):
            # 维护窗口 w1
            d1[a[R]] += 1
            if d1[a[R]] == 1:
                c1 += 1
            while L1 < R and c1 > k:
                d1[a[L1]] -= 1
                if d1[a[L1]] == 0:
                    c1 -= 1
                L1 += 1
            # 维护窗口 w2
            d2[a[R]] += 1
            if d2[a[R]] == 1:
                c2 += 1
            while L2 <= R and c2 >=k:  # 注意，允许空窗
                d2[a[L2]]-=1
                if d2[a[L2]] == 0:
                    c2-=1
                L2+=1

            ans += L2-L1

            R += 1
        return ans
