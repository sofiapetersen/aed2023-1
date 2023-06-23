#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct coordenada{
    int x;
    int y;
}coord;

typedef struct cel{
    char cidade[100];
    coord pontos;
    struct cel *prox;
}celula;


celula *criar();
void inserir(char nome[100], coord pontos, celula *lista);
void imprimir(celula *lista);
float distancia(int cidade1, int cidade2, celula *lista);
celula *apagar(celula *lista);

int main(){
    int menu, i, n, cid1, cid2;
    char nome[100];
    float dist;
    celula *lista;
    lista = criar();
    coord pontos;
do{

    printf("\nMENU\n1- Inserir cidades\n2- Imprimir cidade\n3- Calcula distancia\n4- Sair\n");
    scanf("%d", &menu);

    switch(menu){
        case 1:
        printf("Quantidade de cidades: ");
        scanf("%d", &n);
        getchar();
        for(i=0; i < n; i++){
            printf("Nome: ");
            gets(nome);
            printf("Coordenada x: ");
            scanf("%d", &pontos.x);
            getchar();
            printf("Coordenada y: ");
            scanf("%d", &pontos.y);
            getchar();
            inserir(nome, pontos, lista);
        }
        break;
        case 2:
        imprimir(lista);
        break;
        case 3:
        printf("Calcular distancia entre:\n");
        printf("Cidade 1: ");
        scanf("%d", &cid1);
        printf("Cidade 2: ");
        scanf("%d", &cid2);
        dist = distancia(cid1, cid2, lista);
        printf("A distancia entre as cidade eh de: %.2f", dist);
        break;
        case 4:
        apagar(lista);
        break;
    }
}while (menu <4);
    return 0;
}

celula *criar(){
    celula *head;
    head = (celula*)malloc(sizeof(celula));
    head->prox = NULL;
    return head;
}

void inserir(char nome[100], coord pontos, celula *lista){
    celula *nova, *fim;
    nova = (celula*)malloc(sizeof(celula));
    for(fim = lista; fim->prox != NULL; fim = fim->prox);
    strcpy(nova->cidade, nome);
    nova->pontos.x = pontos.x;
    nova->pontos.y = pontos.y;
    nova->prox = fim->prox;
    fim->prox = nova;
}

void imprimir(celula *lista){
    celula *p;
    int i=0;
    for(p = lista->prox; p != NULL; p = p->prox, i++){
        printf("CIDADE %d", i);
        printf("\nNome: %s ", p->cidade);
        printf("(%d, %d)", p->pontos.x, p->pontos.y);
        printf("\n");
    }
}

float distancia(int cidade1, int cidade2, celula *lista){
    int i=0, j=0;
    float distancia;
    celula *p, *q;
    for(p = lista->prox; p != NULL && i != cidade1; p = p->prox, i++);
    for(p = lista->prox; p != NULL && j != cidade2; p = p->prox, j++);

    distancia = sqrt(pow(p->pontos.x - q->pontos.x, 2) + pow(p->pontos.y - q->pontos.y, 2));
    return distancia;

}

celula *apagar(celula *lista){
    celula *p = lista, *temp = NULL;
    while(p!=NULL){
        temp = p->prox;
        free(p);
        p = temp;
    }
    return NULL;
}