#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//a arvore redblack é boa pra quando precisa inserir muitas coisas, pq nao precisa ficar calculando balanceamento, as cores já aproximam o balanço
// mas na busca ela perde um pouco a eficacia justamente por nao ser calculadamente balanceada e sim uma aproximação

typedef struct Node{
    int data;
    int color;  // 0 preto || 1 vermelho
    struct Node *parent;
    struct Node *right;
    struct Node *left;
}node;

node *uncle ( node *n );
node *grandparent ( node *n );
void insertCase1 ( node *root, node *n );
void insertCase2 ( node *root, node *n );
void insertCase3 ( node *root, node *n );
void insertCase4 ( node *root, node *n );
void insertCase5 ( node *root, node *n );
void printTree(node *root, int level);
void RSE( node *root );
void RSD( node *root );

int main(){

    int nodes;
    node *root = NULL;

    printf( "Nodes: " );
    scanf( "%d", &nodes );
    srand( time( 0 ) );

    for(int i = 0; i < nodes; i++){
        node *new = ( node * )malloc( sizeof( node ) );
        new->data = rand() % 100;
        new->color = 1;         //novo nó sempre eh vermelho
        new->right = new->left = new->parent = NULL;

        if ( root == NULL ){
            root = new;
            root->color = 0;
        } else {
            insertCase1 ( root, new );
        }
        printf( "Insertion complete\n" );
        printTree( root, 0 );
    }

    return 0;
}


node *grandparent ( node *n ){
    if( n != NULL && n->parent != NULL )
        return n->parent->parent;
    else
        return NULL;
}

node *uncle ( node *n ){

    node *g = grandparent( n );
    if( g == NULL )
        return NULL;       //pq se nao tem grandparent nao tem uncle
    if( n->parent == g->left )
        return g->right;
    else
        return g->left;
}

//primeiro insert vai ser o que cria a raiz

void insertCase1 ( node *root, node *n ){
    if( n->parent == NULL ){
        n->color = 0;
        root = n;
    } else
        insertCase2( root, n );
}

void insertCase2 ( node *root, node *n ){
    if( n->parent->color == 0 )
        return; //pq daí a arvore ta certa, o nó a ser inserido sempre é 
    else        //vermelho se n sofrer correcao, entao se o pai ja for preto ent ja ta no lugar certo
        insertCase3( root, n );
}

void insertCase3 ( node *root, node *n ){        //o case3 resolve o problema caso o uncle seja vermelho
    node *g = grandparent( n );
    node *u = uncle ( g );
    if ( ( u != NULL ) && ( u->color == 1 ) ){
        n->parent->color = 0;       //vai pintar o parent de preto
        u->color = 0;               //pinta o uncle de preto também
        g = grandparent( n );
        g->color = 1;               //e pinta o grandparent de vermelho
        insertCase1( root, n );
    } else
        insertCase4( root, n );
}

//até entao todos os casos ja tava balanceado, so tava faltando arrumar as cores
//a partir do case4 começam as rotações pra balancear o que ficou errado

void insertCase4 ( node *root, node *n ){       //pra quando o uncle for preto e o new é filho a esquerda
    node *g = grandparent( n );

    if( n == n->parent->right && n->parent == g->parent->left ){
        RSE( n->parent );
        n = n->left;
    } else if ( n == n->parent->left && n->parent == g->parent->right ){
        RSD ( n->parent );
        n = n->right;
    }

    insertCase5 (root, n );
}

void insertCase5 ( node *root, node *n ){    //quando o uncle for preto e o new é filho a direita

    node *g = grandparent ( n );

    if ( n == n->parent->left && n->parent == g->parent->left )
        RSD ( g );
    if ( n == n->parent->right && n->parent == g->parent->right )
        RSE ( g );

    n->parent->color = 0;
    g->color = 1;

}

void RSE(node *root) {
    node *aux = (root)->right;
    (root)->right = aux->left;
    aux->left = (root);
    (root) = aux;
}

void RSD(node *root) {
    node *aux = (root)->left;
    (root)->left = aux->right;
    aux->right = (root);
    (root) = aux;
}

void printTree(node *root, int level) {
    int i;
    if (root != NULL) {
        printTree(root->left, level + 1);
        for (i = 0; i < level; i++) printf("    ");
        printf("%d\n", root->data);
        printTree(root->right, level + 1);
    }
}