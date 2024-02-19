from collections import defaultdict
from typing import List


class Solution:
    def longestEqualSubarray(self, a: List[int], k: int) -> int:
        d = defaultdict(int)
        ans = 0
        L = R = 0
        while R < len(a):
            d[a[R]] += 1
            ans = max(ans, d[a[R]])
            # 窗口的大小至少为 ans+k
            # 后续遇到更高频的, 窗口才会扩张
            while L < R and ans +k < R-L+1:
                d[a[L]] -=1
                L+=1
            R += 1
        return ans
