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
    ListNode *sortList(ListNode *head) {
        if(!head)
        	return NULL;
        return mergeSort(head);
    }
    ListNode* mergeSort(ListNode *head) {
    	if(!head->next)
    		return head;
    	int length,i;
    	ListNode *temp=head,*p=head,*q=head,*result=NULL;
    	for(length=0;temp!=NULL;++length)
    		temp=temp->next;
    	temp=head;
    	for(i=0;temp!=NULL&&i<length/2-1;++i)
    		temp=temp->next;
    	q=temp->next;
    	temp->next=NULL;
    	p=mergeSort(p);
    	q=mergeSort(q);
    	result=merge(p,q);
    	return result;
    }
    ListNode* merge(ListNode *p,ListNode *q) {
    	ListNode *result=NULL,*temp=NULL;
    	if(p->val<=q->val) {
    		temp=p;
    		p=p->next;
    		temp->next=NULL;
    	}
    	else {
    		temp=q;
    		q=q->next;
    		temp->next=NULL;	
    	}
    	result=temp;
    	while(p&&q) {
    		if(p->val<=q->val){
    			temp=(temp->next=p);
    			p=p->next;
    			temp->next=NULL;
    		}
    		else {
    			temp=(temp->next=q);
    			q=q->next;
    			temp->next=NULL;
    		}
    	}
    	if(p)
    		temp->next=p;
    	if(q)
    		temp->next=q;
    	return result;
    }
};