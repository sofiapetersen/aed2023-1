/*
1669. Merge In Between Linked Lists
You are given two linked lists: list1 and list2 of sizes n and m respectively.

Remove list1's nodes from the ath node to the bth node, and put list2 in their place.

The blue edges and nodes in the following figure indicate the result:
*image*
Build the result list and return its head.
*/


/*
  Definition for singly-linked list.
  struct ListNode {
      int val;
      struct ListNode *next;
  };
 */


struct ListNode* mergeInBetween(struct ListNode* list1, int a, int b, struct ListNode* list2){
    int i;
    struct ListNode *lista, *p, *antesA, *depoisB;
        lista = (struct ListNode*)malloc(sizeof(struct ListNode));
        lista->next = list1;

        p = lista;
        for(i=0; i<a; i++){
            p = p->next;
        }
        antesA = p;

        for(i=a; i<=b+1; i++){
            p = p->next;
        }
        depoisB = p;
        antesA->next = list2;

        while(list2->next != NULL){
            list2 = list2->next;
        }
        list2->next = depoisB;
        return lista->next;

}