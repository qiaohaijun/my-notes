class Solution(object):
    def lengthOfLongestSubstring(self, s):
        ans = 0
        # left用于记录合法的左边界位置，last用于记录字符上一次出现的位置
        left = 0
        last = {}
        for i in range(len(s)):
            # 子串中出现重复字符，变更left至上一次s[i]出现位置之后，使得子串合法
            if s[i] in last and last[s[i]] >= left:
                left = last[s[i]] + 1
            last[s[i]] = i
            ans = max(ans, i - left + 1)
        return ans
