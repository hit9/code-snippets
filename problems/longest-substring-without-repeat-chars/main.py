from collections import defaultdict


class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if len(s) == 0:
            return 0
        d = defaultdict(int)  # 窗口内的元素频次
        c = 0  # 窗口内的元素种类
        L = R = 0
        ans = 1
        while R < len(s):
            # 右边是负责做事情
            d[s[R]] += 1
            if d[s[R]] == 1:
                c += 1
            # 左边负责撤销, 保证窗口满足限制
            while L < R and c < R - L + 1:
                d[s[L]] -= 1
                if d[s[L]] == 0:
                    c -= 1
                L += 1

            ans = max([ans, R - L + 1])

            R += 1
        return ans
