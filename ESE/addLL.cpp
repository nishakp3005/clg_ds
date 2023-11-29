// Definition for singly-linked list.
#include<bits/stdc++.h>

 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode* dummy = new ListNode(0);  // Dummy node to simplify code
        ListNode* temp1 = l1;
        ListNode* temp2 = l2;
        ListNode* current = dummy;

        while (temp1 != nullptr || temp2 != nullptr || carry != 0) {
            int a = (temp1 != nullptr) ? temp1->val : 0;
            int b = (temp2 != nullptr) ? temp2->val : 0;
            int sum = a + b + carry;

            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;

            if (temp1 != nullptr) temp1 = temp1->next;
            if (temp2 != nullptr) temp2 = temp2->next;
        }

        return dummy->next;  // Skip the dummy node
    }
};
