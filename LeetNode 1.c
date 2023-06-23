/*
876. Middle of the Linked List:
Given the head of a singly linked list, return the middle node of the linked list.
If there are two middle nodes, return the second middle node.
*/

/*
  Definition for singly-linked list.
  struct ListNode {
      int val;
      struct ListNode *next;
  };
 */
struct ListNode* middleNode(struct ListNode* head){
        struct ListNode *p, *q;   //cria dois ponteiros
        p = head;       // os dois vao estar apontando pra cabeça da lista
        q = head;
        while(p != NULL && p->next != NULL){        
            q = q->next;                // o ponteiro q vai andar 1 nó, enquanto o p anda 2 nós por ciclo do while
            p = p->next->next;              // então quando o p / p->next chegar no final (NULL) o q vai estar no meio da lista;
        }
        return q;
}