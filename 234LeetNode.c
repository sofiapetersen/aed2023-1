#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

 struct ListNode {
     int val;
    struct ListNode *next;
     };

bool isPalindrome(struct ListNode* head);
struct ListNode *create();
 
int main(){

struct ListNode *head = create();

bool result = isPalindrome(head);

if(result){
    printf("It is a palindrome");
}
else{
    printf("It isnt a palindrome");
}


    return 0;
}

struct ListNode *create(){
    struct ListNode *head, *tail;
    head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next = NULL;
    tail = head;

    int value;
    while(1){
        printf("Type one number (-1 to stop): ");
        scanf("%d", &value);
        if (value == -1)
        break;

 struct ListNode *new = (struct ListNode*)malloc(sizeof(struct ListNode)); //alocando proximo nó
       new->val = value;
        new->next = NULL;

        if (head == NULL) {
            head = new;
            tail = new;
        } else {
            tail->next = new;
            tail = tail->next;
        }
    }

    return head;
    }

bool isPalindrome(struct ListNode* head){
        struct ListNode *slow = head, *fast = head, *prev, *temp;

        while(fast != NULL && fast->next != NULL){
                slow = slow->next;
                fast = fast->next->next;
        } 

        //esse while anterior foi pra conseguir "dividir" a lista em 2, pq o slow chega no meio enquanto o fast chega no final da lista.

        prev = slow;
        slow = slow->next;
        prev->next = NULL;

        // ai aqui vai de fato dividir a lista pq o prev passa a ser o meio da lista e o slow o proximo nó, dai o prev->next fica NULL pra ter um espaço entre os dois. Assim a lista ficou dividida em 2 partes iguais

        while(slow != NULL){
                temp = slow->next;
                slow->next = prev;
                prev = slow;
                slow = temp;
        }

        // nesse while vai passar pela segunda lista ao contrario, ou seja, inverte ela pra ver se vai ficar igual a primeira (levando em consideracao que o palindromo vai e volta e a volta deve ser igual, espelhada. dai pra comparar cloca as duas igual), dai o prev volta a ser o inicio desse lista

        // ou seja, era 1221 -> passa a ser 12 21 -> dai nesse while inverte -> 12 12

        fast = head; //aqui o fast vai pro inicio da primeira metade
        slow = prev; //aqui o slow vai pro inicio da segunda metade

        //fast ta apontando pro 1 do 12  // o slow aponta pro 1 do segundo 12
        
        while(slow != NULL){
                if(fast->val != slow->val){
                return false;}
                fast = fast->next;
                slow = slow->next;
        }

        // esse ultimo while percorre as duas listas e ve se sao iguais, se nao entrar no if (numeros diferentes) entao sao palindromas e retorna true
        return true;
}