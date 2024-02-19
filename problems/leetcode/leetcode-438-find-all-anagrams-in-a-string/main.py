from collections import defaultdict
from typing import List


class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        d = defaultdict(int)  # p 中的各个字符的出现次数
        a = 0  # p 中不同的字符个数
        for ch in p:
            d[ch] += 1
            if d[ch] == 1:
                a += 1

        b = 0  # b 是窗口内的扣减了 p 中字符的种类数
        ans = []

        L = R = 0

        while R < len(s):
            # 扣减出现频次,
            d[s[R]]-=1
            # 并且, 如果扣减后是 0 , 则记录一次 b
            if d[s[R]] == 0:
                b += 1

            while L < R and R - L + 1 > len(p):
                # 恢复出现频次
                d[s[L]] += 1
                # 如果恢复前是 0, 则也要恢复 b
                if d[s[L]] == 1:
                    b -= 1
                L += 1

            if a == b:
                ans.append(L)

            R += 1
        return ans
