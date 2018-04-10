/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// remainder 余数
// carry 进位

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
      
      ListNode* dummy = new ListNode(-1);
      ListNode* res = dummy;
      
      int remainder = 0;
      int carry = 0;
      
      while(l1!=NULL && l2!=NULL) {
        int sum = carry + l1->val + l2->val;
        remainder = sum % 10;
        carry = sum / 10;
        res->next = new ListNode(remainder);
        l1 = l1->next;
        l2 = l2->next;
        res=res->next;
      }
      
      while(l1!=NULL){
        int sum = carry+l1->val;
        remainder = sum % 10;
        carry = sum / 10;
        res->next = new ListNode(remainder);
        l1 = l1->next;
        res=res->next;

      }
      while(l2!=NULL){
        int sum = carry+l2->val;
        remainder = sum % 10;
        carry = sum / 10;
        res->next = new ListNode(remainder);
        l2 = l2->next;
        res=res->next;

      }
      if(carry>0) {
        res->next = new ListNode(carry);
      }
      return dummy->next;
    }
};
