#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cel{
    char palavra[100];
    struct cel *prox;
};

typedef struct cel celula;

celula *criar();
void insere(char word[100], celula *p);
void imprimir(celula *p_ini);
celula *apaga(celula *ini);

int main(){
    char palavra[100];

    celula *ini;
    ini = criar();

    printf("Escreva: ");
    gets(palavra);

    insere(palavra, ini);
    imprimir(ini);
    apaga(ini);

    return 0;
}

celula *criar(){
    celula *head;
    head = (celula*)malloc(sizeof(celula));
    head->prox = NULL;
    return head;
}

void insere(char word[100], celula *p){
    celula *nova;

    nova = (celula *)malloc(sizeof(celula));
    strcpy(nova->palavra, word);
    nova->prox = p->prox;
    p->prox = nova;
}

void imprimir( celula *p_ini){
    celula *p;
    int tamanhoV, i, j;
    char vogal[] = "aeiouAEIOU";

    tamanhoV = strlen(vogal);

    for(p = p_ini->prox; p != NULL; p = p->prox){
        for(i=0; i < strlen(p->palavra); i++){

        for(j=0; j < tamanhoV; j++){
            if(p->palavra[i] == vogal[j])
            break;
        }
        if(j == tamanhoV){
            printf("%c", p->palavra[i]);
        }
    }
    printf("\n");

        printf("Palavra original: %s", p->palavra);
    }
}


celula *apaga(celula *ini){
    celula *p = ini, *temp = NULL;
    while(p != NULL){
        temp = p->prox;
        free(p);
        p = temp;
    }
    return NULL;
}
