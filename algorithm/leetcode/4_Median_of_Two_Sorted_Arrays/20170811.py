class Solution(object):
    def findKth(self,A,B,k):
        if len(A) == 0:
            return B[k-1]
        if len(B) == 0:
            return A[k-1]
        
        if len(A) > len(B):
            return self.findKth(B,A,k)
        if k==1:
            return min(A[0],B[0])
        
        pa = min(len(A), k/2)
        pb = k-pa
        
        if A[pa-1] < B[pb-1]:
            return self.findKth(A[pa:],B,k-pa)
        elif A[pa-1] > B[pb-1]:
            return self.findKth(A,B[pb:],k-pb)
        else:
            return A[pa-1]
        
        
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        total_len =len(nums1)+len(nums2)
        if total_len%2 ==1:
            return self.findKth(nums1,nums2,total_len/2+1)/1
        else:
            return self.findKth(nums1,nums2,total_len/2)/2.+self.findKth(nums1,nums2,total_len/2+1)/2.
