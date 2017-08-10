# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def addTwoNumbers(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        ret_node = ListNode(-1)
        vis_node = ret_node
        x = 0
        y = 0
        carry = 0
        remain = 0
        while (l1 is not None) or (l2 is not None):
            x = 0
            y = 0
            local_sum = 0
            if l1 is not None:
                x = l1.val
                l1 = l1.next
            if l2 is not None:
                y = l2.val
                l2 = l2.next
            local_sum = carry+x+y
            carry = local_sum/10
            remain = local_sum%10
            vis_node.next = ListNode(remain)
            vis_node = vis_node.next
        
        if carry!= 0:
            vis_node.next = ListNode(carry)
        
        return ret_node.next
            
            
