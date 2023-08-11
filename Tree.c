#include <stdio.h>
#include <stdlib.h>

typedef long TipoChave;

typedef struct Registro {
    TipoChave Chave;
    /* outros componentes */
} Registro;

typedef struct No No;  // Removed the "*" from "struct No *"
typedef No* Apontador;
typedef Apontador TipoDicionario;

struct No { // Corrected "Struct" to "struct"
    Registro Reg;
    Apontador pEsq, pDir;
};


int FB (No* pRaiz);
int Altura(No* pRaiz);
int Push(No** ppRaiz, Registro* x);
int Balanceamento(No** ppRaiz);
void RSE(No** ppRaiz);
void RSD(No** ppRaiz);
int BalancaEsquerda(No** ppRaiz);
int BalancaDireita(No** ppRaiz);
int EhArvoreAvl(No* pRaiz);
void PrintTree(No* pRaiz, int nivel);
void FreeTree(No* pRaiz);


int main(){

    TipoDicionario arvore = NULL;
    Registro registro;
    char opcao;

    do {
        printf("Digite o valor da chave: ");
        scanf("%ld", &registro.Chave);

        if (Push(&arvore, &registro)) {
            printf("Insercao realizada com sucesso.\n");
        } else {
            printf("Erro na insercao.\n");
        }

        PrintTree(arvore, 0);

        if (EhArvoreAvl(arvore)) {
            printf("A arvore eh AVL.\n");
        } else {
            printf("A arvore nao eh AVL.\n");
        }

        printf("Deseja inserir mais um elemento? (S/N): ");
        scanf(" %c", &opcao);
    } while (opcao == 'S' || opcao == 's');

    FreeTree(arvore);
    return 0;
}



int FB (No* pRaiz){
    if (pRaiz == NULL)
        return 0;
    return Altura(pRaiz->pEsq) - Altura(pRaiz->pDir);
}

int Altura(No* pRaiz){
    int iEsq,iDir;
    if (pRaiz == NULL)
        return 0;
    iEsq = Altura(pRaiz->pEsq);
    iDir = Altura(pRaiz->pDir);
    if ( iEsq > iDir )
        return iEsq + 1;
    else
    return iDir + 1;
}

int Push(No** ppRaiz, Registro* x) {
    if (*ppRaiz == NULL) {
        *ppRaiz = (No*)malloc(sizeof(No));
        (*ppRaiz)->Reg = *x;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;
        return 1;  // Added the missing semicolon
    } else if ((*ppRaiz)->Reg.Chave > x->Chave) {  // se o novo for menor que o q ja tem, entra na direita
        if (Push(&(*ppRaiz)->pEsq, x)) {    //dai ele entra no push de novo, faz aquele ali do nó nulo e volta pra cá
            if (Balanceamento(ppRaiz))  //confere o balanceamento
                return 0;
            else
                return 1;
        }
    } else if ((*ppRaiz)->Reg.Chave < x->Chave) {  // se o novo for maior que o q ja tem, entra na esquerda
        if (Push(&(*ppRaiz)->pDir, x)) {
            if (Balanceamento(ppRaiz))
                return 0;
            else
                return 1;
        } else
            return 0;
    } else
        return 0;
}

int Balanceamento(No** ppRaiz){
    int fb = FB(*ppRaiz);
    if ( fb > 1)
        return BalancaEsquerda(ppRaiz);
    else if (fb <-1 )
        return BalancaDireita(ppRaiz);
    else
        return 0;
}

void RSE(No** ppRaiz){
    No *pAux;
    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;
}

void RSD(No** ppRaiz){
    No *pAux;
    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;
}

int BalancaEsquerda(No** ppRaiz){
    int fbe = FB ( (*ppRaiz)->pEsq );
    if ( fbe > 0 ){
        RSD(ppRaiz);
        return 1;
    }
    else if (fbe < 0 ){ /* Rotação Dupla Direita */
        RSE( &((*ppRaiz)->pEsq) );
        RSD( ppRaiz ); /* &(*ppRaiz) */
        return 1;
    }
    return 0;
}

int BalancaDireita(No** ppRaiz){
    int fbd = FB((*ppRaiz)->pDir);
    if(fbd < 0){
        RSE(ppRaiz);
        return 0;
    }
    else if(fbd > 0){
        RSD(&((*ppRaiz)->pEsq));
        RSE(ppRaiz);
        return 0;
    }
}

int EhArvoreAvl(No* pRaiz){
    int fb;
    if (pRaiz == NULL)
        return 1;
    if (!EhArvoreAvl(pRaiz->pEsq))
        return 0;
    if (!EhArvoreAvl(pRaiz->pDir))
        return 0;

    fb = FB (pRaiz);
    if ( ( fb > 1 ) || ( fb <-1) )
        return 0;
    else
        return 1;
}

void PrintTree(No* pRaiz, int nivel) {
    int i;
    if (pRaiz != NULL) {
        PrintTree(pRaiz->pDir, nivel + 1);
        for (i = 0; i < nivel; i++) printf("    ");
        printf("%ld\n", pRaiz->Reg.Chave);
        PrintTree(pRaiz->pEsq, nivel + 1);
    }
}

void FreeTree(No* pRaiz) {
    if (pRaiz != NULL) {
        FreeTree(pRaiz->pEsq);
        FreeTree(pRaiz->pDir);
        free(pRaiz);  // Free the current node
    }
}