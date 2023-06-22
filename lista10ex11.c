#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cel{
    char sobrenome[100];
    int matricula;
    int ano;
    celula *prox;
}celula;

celula *criar();
void insereFim(char sobrenome, int matricula, int data, celula *p);

int main(){
    int alunos, i, id, nascimento;
    char nome[100];
    celula *lista;
    lista = criar();

    printf("Digite a quantidade de alunos: ");
    scanf("%d", &alunos);
    getchar();

    for(i=0;i<alunos;i++){
        printf("\nSobrenome: ");
        gets(nome);
        getchar();
        printf("\nMatricula: ");
        scanf("%d", &id);
        printf("\nAno de nascimento: ");
        scanf("%d", &nascimento);
        insereFim(nome, id, nascimento, lista);  
    }

}

celula *criar(){
    celula *head;
    head = (celula *)malloc(sizeof(celula));
    head->prox = NULL;
    return head;
}

void insereFim(char nomes, int matriculas, int datas, celula *p){
    celula *nova;
    nova = (celula *)malloc(sizeof(celula));
    strcpy(nova->sobrenome, nomes);
    nova->matricula = matriculas;
    nova->ano = datas;
    nova->prox = p->prox;
    p->prox = nova;

}