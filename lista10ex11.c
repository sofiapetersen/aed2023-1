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
void insereFim(char nomes[100], int matriculas, int datas, celula *lista);
void imprimir(celula *lista);
celula *apagar(celula *lista);

int main(){
    int alunos, i, id, nascimento, menu;
    char nome[100];
    celula *lista;
    lista = criar();
    do{
    printf("\nMENU\n1- Inserir alunos\n2- Imprimir matriculas\n3- Sair\nEscolha uma opcao: ");
    scanf("%d", &menu);

    switch(menu){
        case 1:
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
        break;
        case 2:
        imprimir(lista);
        break;
        case 3:
        apagar(lista);
        break;
    }
    }while(menu < 3);

    return 0;
}

celula *criar(){
    celula *head;
    head = (celula *)malloc(sizeof(celula));
    head->prox = NULL;
    return head;
}

void insereFim(char nomes[100], int matriculas, int datas, celula *lista){
    celula *nova, *fim;
    for(fim = lista; fim->prox !=NULL; fim = fim->prox);
    nova = (celula *)malloc(sizeof(celula));
    strcpy(nova->sobrenome, nomes);
    nova->matricula = matriculas;
    nova->ano = datas;
    nova->prox = fim->prox;
    fim->prox = nova;
    
}

void imprimir(celula *lista){
    celula *p;
    int i=0;
    for(p = lista->prox; p != NULL; p = p->prox,i++){
        printf("\nALUNO %d", i+1);
        printf("\nSobrenome: %s", p->sobrenome);
        printf("\nMatricula: %d", p->matricula);
        printf("\nAno: %d", p->ano);
        printf("\n");
    }

}

celula *apagar(celula *lista){
    celula *p = lista, *temp = NULL;
    while(p != NULL){
        temp = p->prox;
        free(p);
        p = temp;
    }
    return NULL;
}
