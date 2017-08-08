class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        ret = list()
        dictOfNum = dict()
        
        # build dict
        for idx, val in enumerate(nums):
            dictOfNum[val] = idx
            
        #
        for idx, val in enumerate(nums):
            otherNum = target -val
            if((otherNum) in dictOfNum ) and dictOfNum[otherNum]>idx:
                ret.append(idx)
                ret.append(dictOfNum[otherNum])
        
        return ret
