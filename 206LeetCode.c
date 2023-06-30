/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head){
        struct ListNode *atual = head, *prev = NULL;

        while(atual != NULL){
                struct ListNode *nova = atual->next;
                atual->next = prev;
                prev = atual;
                atual = nova;
        }
        return prev;
}
