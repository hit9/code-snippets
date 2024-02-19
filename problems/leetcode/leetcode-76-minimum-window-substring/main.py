from collections import defaultdict


class Solution:
    def minWindow(self, s: str, t: str) -> str:
        d1 = defaultdict(int)  # t 内的字符频次计数
        c = 0  # 还需要统计的字符种类, 初始化为 t 中的字符种类
        for ch in t:
            d1[ch] += 1
            if d1[ch] == 1:
                c += 1

        d2 = defaultdict(int)  # 窗口内的字符频次计数

        ans_L = 0
        ans_size = 0x3F3F3F3F

        L = R = 0
        while R < len(s):
            # 维护右端: 窗口内计数+1
            # 并且如果是需要的字符, 则维护需要的种类 c
            d2[s[R]] += 1
            if d2[s[R]] == d1[s[R]]:
                c -= 1
            # 维护左端: 左端 L 字符的出现次数超过 t 中的
            while L < R and d2[s[L]] > d1[s[L]]:
                d2[s[L]] -= 1
                L += 1
            # 维护答案
            if c == 0 and ans_size > R - L + 1:
                ans_L, ans_size = L, R - L + 1

            R += 1
        if ans_size > len(s):
            return ""
        return s[ans_L : ans_L + ans_size]
