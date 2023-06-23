#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cel{
    char nome[50];
    int codigo;
    int estoque;
    float valor;
    struct cel *prox;
    struct cel *prev;
}celula;

celula *criar();
void inserir(int codigo, char nome[50], int estoque, float valor, celula *lista);
void imprimir(celula *lista);
int valorAlto(celula *lista);

int main(){

    int menu, id, qntd, maisCaro;
    float preco;
    char produto[500];

    celula *lista;
    lista = criar();

do{
    printf("\nMENU\n1- Adicionar produto\n2- Imprimir produtos\n3- Valor mais alto\n4- Produto com mais estoque\n5- Sair\nEscolha: ");
    scanf("%d", &menu);

    switch(menu){
        case 1:
        printf("Codigo: ");
        scanf("%d", &id);
        getchar();
        printf("Nome: ");
        gets(produto);
        printf("Quantidade em estoque: ");
        scanf("%d", &qntd);
        getchar();
        printf("Valor: ");
        scanf("%f", &preco);
        inserir(id, produto, qntd, preco, lista);
        break;
        
        case 2:
        imprimir(lista);
        break;

        case 3:
        maisCaro = valorAlto(lista);
        printf("O produto com valor mais alto eh: codigo %d", maisCaro);
        break;
    }

}while(menu <5);

    return 0;
}

celula *criar(){
    celula *head;
    head = (celula*)malloc(sizeof(celula));
    head->prox = NULL;
    head->prev = NULL;
    return head;
}

void inserir(int codigo, char nome[50], int estoque, float valor, celula *lista){
    celula *nova, *fim;
    nova = (celula*)malloc(sizeof(celula));
    for(fim = lista; fim->prox != NULL; fim = fim->prox);
    nova->codigo = codigo;
    strcpy(nova->nome, nome);
    nova->estoque = estoque;
    nova->valor = valor;
    nova->prox = fim->prox;
    fim->prox = nova;
    nova->prev = fim;
}

void imprimir(celula *lista){
    celula *p;
    int i;
    for(p = lista->prox, i=0; p != NULL; p = p->prox, i++){
        printf("\nPRODUTO %d", i);
        printf("\nCodigo: %d", p->codigo);
        printf("\nNome: %s", p->nome);
        printf("\nEstoque: %d unidades", p->estoque);
        printf("\nValor: %.2f", p->valor);
        printf("\n");
    }
}

int valorAlto(celula *lista){
    celula *p;
    int i=-1;
    float preco=0;
    for(p = lista->prox; p != NULL; p = p->prox);
        if(p->valor > preco){
            preco = p->valor;
            i++;
        }
    return i;
}