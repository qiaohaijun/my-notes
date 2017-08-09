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
        
                
        if l1 is None:
            return l2
        if l2 is None:
            return l1
        
        
        carry = 0
        
        ret_node = None
        vis_node = None
        while (l1 is not None) and (l2 is not None):
            local_sum = l1.val+l2.val+carry
            carry = int(local_sum/10)
            remain = local_sum%10

            cur_node = ListNode(remain)

            if vis_node is None:
                vis_node = cur_node
                ret_node = vis_node
            else:
                vis_node.next = cur_node
                vis_node = vis_node.next
            l1 = l1.next
            l2 = l2.next
        
        while (l1 is not None) and (l2 is None):
            local_sum = l1.val+carry
            carry = int(local_sum/10)
            remain = local_sum%10

            cur_node = ListNode(remain)

            if vis_node is None:
                vis_node = cur_node
                ret_node = vis_node
            else:
                vis_node.next = cur_node
                vis_node = vis_node.next
            l1 = l1.next
        while (l1 is None) and (l2 is not None):
            local_sum = l2.val+carry
            carry = int(local_sum/10)
            remain = local_sum%10
            cur_node = ListNode(remain)

            if vis_node is None:
                vis_node = cur_node
                ret_node = vis_node
            else:
                vis_node.next = cur_node
                vis_node = vis_node.next
            l2 = l2.next
        if carry != 0:
            cur_node = ListNode(carry)
            print carry
            if vis_node is None:
                vis_node = cur_node
                ret_node = vis_node
            else:
                vis_node.next = cur_node
                vis_node = vis_node.next

        return ret_node
