#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cel{
    char sobrenome[100];
    int matricula;
    int ano;
    struct cel *prox;
}celula;

celula *criar();
void insereFim(char nomes[100], int matriculas, int datas, celula *p);

int main(){
    int alunos, i, id, nascimento;
    char nome[100];
    celula *lista;
    lista = criar();

    printf("Digite a quantidade de alunos: ");
    scanf("%d", &alunos);
    getchar();
    for(i=0;i<alunos;i++){
        printf("INSCRICAO DO ALUNO %d\n", i+1);
        printf("Sobrenome: ");
        gets(nome);
        printf("Matricula: ");
        scanf("%d", &id);
        getchar();
        printf("Ano de nascimento: ");
        scanf("%d", &nascimento);
        getchar();
        printf("\n");
        insereFim(nome, id, nascimento, lista);  
    }

}

celula *criar(){
    celula *head;
    head = (celula *)malloc(sizeof(celula));
    head->prox = NULL;
    return head;
}

void insereFim(char nomes[100], int matriculas, int datas, celula *p){
    celula *nova;
    nova = (celula *)malloc(sizeof(celula));
    strcpy(nova->sobrenome, nomes);
    nova->matricula = matriculas;
    nova->ano = datas;
    nova->prox = p->prox;
    p->prox = nova;

}