#include <stdio.h>
#include <stdlib.h>

struct cel{
    int n;
    struct cel *prox;
};

typedef struct cel celula;

celula *criar();
void insereFim(int numero, celula *p_ini);
int contaPar(celula *p_ini);
int contaImpar(celula *p_ini);
void imprimir(celula *ini);
void insere(int ns, celula *p);

int main(){

    int i, x, num, par, impar;
    celula *ini;
    ini = criar();

    printf("tamanho do vetor: ");
    scanf("%d", &x);

    for(i=0;i<x;i++){
        printf("digite um numero: ");
        scanf("%d", &num);
        insereFim(num, ini);
    }

    par = contaPar(ini);
    printf("Quantidade de numeros par: %d\n", par);

    impar = contaImpar(ini);
    printf("Quantidade de numero impar: %d", impar);

    printf("\nOs numeros:");
    imprimir(ini);
    return 0;
}


celula *criar(){
    celula *head;
    head = (celula *) malloc(sizeof(celula));
    head->prox = NULL;
    return head;
}

void insereFim(int numero, celula *p_ini){
    celula *nova, *fim;
    for(fim = p_ini; fim->prox != NULL; fim= fim->prox);
    nova = (celula *)malloc(sizeof(celula));
    nova->n = numero;
    nova->prox = fim->prox;
    fim->prox = nova;

}

void insere(int ns, celula *p){
    celula *nova;

    nova = (celula *)malloc(sizeof(celula));
    nova->n = ns;
    nova->prox = p->prox;
    p->prox = nova;
}

int contaPar( celula *p_ini){
    celula *p;
    int par=0;
    
    for(p = p_ini->prox; p != NULL; p = p->prox){
        if (p->n % 2 == 0){
            par++;
        }
    }
    return par;
}

int contaImpar(celula *p_ini){
    celula *p;
    int impar=0;
    for(p = p_ini->prox; p != NULL; p = p->prox){
        if(p->n % 2 != 0){
            impar++;
        }
    }
    return impar;
}

void imprimir(celula *ini){
    celula *p;
    for(p = ini->prox; p != NULL; p = p->prox){
        printf("\n%d", p->n);
    }
}
