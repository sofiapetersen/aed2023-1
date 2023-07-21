#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct structData_t{
    int code;
    int name[50];
    float price;
};
typedef struct structData_t sData;

struct structNode_t{
    sData info;
    struct sNode *pNext;
};
typedef struct structNode_t sNode;

struct structS_t{
    sNode *pFirst;
};
typedef struct structS_t sList;

void Clear ( sList *pList );
void Reset ( sList *pList );

int main(  ){

    return 0;
}

void Clear ( sList *pList ){
    sNode *current = pList -> pFirst;   //ponteiro current aponta pra cabeça
    while( current != NULL ){   
        sNode *next = current->pNext;       //ponteiro next aponta pro current->next
        free(current);      //libera o current
        current = next;     // current recebe o next, dai enquanto ele nao for NULL o looping continua até desalocar todos
    }
    pList->pFirst = NULL; //dai garante que a cabeça ta vazia

}

void Reset ( sList *pList ){
    Clear( pList );

    pList = ( sList* ) malloc ( sizeof ( sList ) );
}


