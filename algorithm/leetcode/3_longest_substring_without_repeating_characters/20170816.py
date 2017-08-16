class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        hashTable = {}
        last = 0
        max_len = 0
        
        for i in range(len(s)):
            if (s[i] in hashTable) and (last <= hashTable[s[i]]):
                last = hashTable[s[i]] +1
                #print s[i],last,i-last+1
                
            hashTable[s[i]] = i
                    
            max_len = max(max_len,i+1-last)
            
        return max_len
            
