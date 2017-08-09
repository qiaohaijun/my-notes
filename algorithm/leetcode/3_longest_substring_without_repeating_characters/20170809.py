class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_len = 0
        local_max = 0

        dictOfStr = dict()
        i = 0
        j = 0
        while j <len(s) and i <len(s):
            if not s[j] in dictOfStr:
                dictOfStr[s[j]] = j
                local_max +=1
                if local_max > max_len:
                    max_len = local_max
            else:  
                local_max -= dictOfStr[s[j]]-i
                for idx in range(i, dictOfStr[s[j]]):
                    del dictOfStr[s[idx]]
                i = dictOfStr[s[j]]+1
                dictOfStr[s[j]]=j
            j+=1

        return max_len        
            
        
