#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 3

typedef struct {            //strct pra definir a fila de prioridade
    int data[MAX];
    int size;
} PriorityQueue;


int Pop(PriorityQueue* pQ);
void Push(PriorityQueue* pQ, int value);
int fillCups(int* amount, int amountSize);

int main(){

    int amount[3] = {0}, size = 3, answer;

    printf("type 0: ");
    scanf("%d", &amount[0]);
    printf("type 1: ");
    scanf("%d", &amount[1]);
    printf("type 2: ");
    scanf("%d", &amount[2]);

    answer = fillCups(amount, size);

    printf("\nAnswer: %d\n", answer);

    return 0;
}

void Reset(PriorityQueue* pQ) {     //cria a fila em 0
    pQ->size = 0;
}

void Push(PriorityQueue* pQ, int value) {       //push de prioridade

    if (pQ->size < MAX) {

        int i = pQ->size;       //aqui vai colocar o indice da fila no final da fila, que no caso é o tamanho dela
        pQ->data[i] = value;        //aqui vai passar pro data[i] o valor que a gnt quer botar
        pQ->size++;         //e aqui vai incrementar o tamanho pra dizer q a fila cresceu

        int big = (i - 1) / 2;  //calculo do heap pra encontrar o indice do maior
        while (i > 0 && pQ->data[big] < pQ->data[i]) {  //confere se o i nao eh a raiz e se o novo nao eh menor q o q ja tem
            int temp = pQ->data[big];
            pQ->data[big] = pQ->data[i];
            pQ->data[i] = temp;     
            //se tiver errado, tem que trocar o maior e colocar ele mais perto da raiz pq eh maior

            i = big;
            big = (i - 1) / 2;  
            //aqui faz seguir o processo de percorrer a heap até chegar na raiz 
        }
    }
}

int Pop(PriorityQueue* pQ) {
    int i = 0, remove = pQ->data[0];   //tira o que tava na raiz e coloca nesse remove
    pQ->size--;         //decrementa a heap
    
    pQ->data[0] = pQ->data[pQ->size];   //aqui é pra remanejar o ultimo da prioridade pra raiz
        while (1) {     //looping infinito
            int left = 2 * i + 1;   //confere o lado esquerdo do heap
            int right = 2 * i + 2;   //confere o lado direito do heap
            int largest = i;

        if (left < pQ->size && pQ->data[left] > pQ->data[largest]) {
            largest = left;
        }

        if (right < pQ->size && pQ->data[right] > pQ->data[largest]) {
            largest = right;
        }

        //nesses dois ifs ele compara ve qual dos lados é maior, 

         if (largest != i) {
            int temp = pQ->data[i];
            pQ->data[i] = pQ->data[largest];
            pQ->data[largest] = temp;

            i = largest;
        } else {
            break;
        }
            //aqui ele olha se o maior é o mesmo do indice, se não for significa que a 
            //ordem de prioridade tá errada entao tem mudar de lugar. se for ele sai do loop pq dai ja ta tudo ok       
    }
        return remove; //retorna o que removeu la no inicio depois de ter ajeitado o resto dos outros
 }

int fillCups(int* amount, int amountSize){
    PriorityQueue pQ;
    Reset(&pQ); //inicializa a fila
    int sec = 0;
    int i, a, b;

    for (i = 0; i < amountSize; i++) {
        Push(&pQ, amount[i]);
    }   //for pra percorrer a array e ir colocando na fila (em prioridade, pq o push eh de prioridade)

    while (pQ.data[0] != 0) {       //entra no while pra ir até o final dos copos
        a = Pop(&pQ);
        b = Pop(&pQ);   //dai aqui vai remover os dois primeiros da fila e armazenar nessas variaveis

        a--;
        b--; //depois decrementa cada um como se tivesse marcando que ja foi usado pra botar no copo

        Push(&pQ, a);
        Push(&pQ, b);   //coloca eles de novo, reduzidos e em ordem de prioridade

        sec++; //cada vez que da esse looping aumenta 1 segundo
    }
    return sec;

}