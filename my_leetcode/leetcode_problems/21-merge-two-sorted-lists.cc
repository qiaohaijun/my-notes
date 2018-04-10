/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
      
      if(l1 == NULL && l2==NULL ) {
        return NULL;
      } 
      else if(l2!=NULL && l1==NULL) {
        return l2;
      }
      else if(l2==NULL && l1!= NULL) {
        return l1;
      }
      
      ListNode *dummy = new ListNode(-1);
      ListNode *my_head = dummy;
      
      while(l1!=NULL && l2!=NULL) 
      {
        if(l1->val < l2->val)
        {
          my_head->next = l1;
          l1=l1->next;
        }
        else {
          my_head->next = l2;
          l2=l2->next;
        }
        my_head = my_head->next;
      }
      
      if(l1!=NULL) {
        my_head->next = l1;

      }
      
      if(l2!=NULL) {
        my_head->next = l2;
      }
      
      return dummy->next;
    }
};
