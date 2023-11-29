
//  Definition for singly-linked list.
 struct ListNode {
    int val;
    struct ListNode *next;
 };

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct ListNode* rotateRight(struct ListNode* head, int k) {
    if(head == NULL) return NULL;
    int len = 1;
    struct ListNode* tail = head;
    struct ListNode* temp;
    while(tail->next != NULL){
        tail = tail->next;
        len++;
    }
    k = k % len;
    if(k == 0) return head;
    temp = head;
    for(int i = 0; i<len-k-1; i++){
        temp = temp->next;
    }
    struct ListNode* newHead = temp->next;
    temp->next = NULL;
    tail->next = head;
    return newHead;
};