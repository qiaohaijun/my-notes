class Solution(object):
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        n = len(nums1) + len(nums2)
        if n % 2 == 1:
            return self.findKth(nums1, nums2, n / 2 + 1)
        else:
            #偶数个，要取两个值的平均值
            smaller = self.findKth(nums1, nums2, n / 2)
            bigger = self.findKth(nums1, nums2, n / 2 + 1)
            return (smaller + bigger) / 2.0

    def findKth(self, nums1, nums2, k):
        if len(nums1) == 0:
            return nums2[k-1]

        if len(nums2) == 0:
            return nums1[k-1]

        if k == 1:
            return min(nums1[0], nums2[0])

        if len(nums1) < k / 2:
            a = None
        else:
            a = nums1[k/2 - 1]

        if len(nums2) < k / 2:
            b = None
        else:
            b = nums2[k/2 - 1]


        if not a:
            return self.findKth(nums1, nums2[k/2:], k - k/2)
        if not b:
            return self.findKth(nums1[k/2:], nums2, k - k/2)
        if a < b:
            return self.findKth(nums1[k/2:], nums2, k - k/2)
        else:
            return self.findKth(nums1, nums2[k/2:], k - k/2)
