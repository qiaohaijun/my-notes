class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        dictOfNum = {}
        ret = []
        
        for i in range(len(nums)):
            dictOfNum[nums[i]] = i
            
        for i in range(len(nums)):
            needed = target - nums[i]
            if needed in dictOfNum and i < dictOfNum[needed]:
                ret.append(i)
                ret.append(dictOfNum[needed])
                break
                
        return ret
