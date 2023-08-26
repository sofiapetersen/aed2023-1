#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} Node;

int Push( Node **root, int val );
int RightBalance( Node **root );
int LeftBalance( Node **root );
int FB( Node *root );
int Size( Node *root );
int Balance( Node **root );
void LeftRotation( Node **root );
void RightRotation( Node **root );
void printTree( Node *root, int level );
void freeTree( Node *root );
int findSecondMinimumValue( Node* root );
void Search ( Node *root, int *value, int *i );
int findMinimumValue( Node* root );

int main() {
    int value;
    Node *root = NULL;

    while (1) {
        printf( "\nAdd a node: " );
        scanf( "%d", &value );
        if ( value == -1 )
            break;
        else {
            if ( Push( &root, value ) ) {
                printf( "\nInsertion correct\n" );
            } else {
                printf( "\nInsertion error\n" );
            }
        }
    }

    printf( "\nThe tree:\n" );
    printTree( root, 0 );
    int min, secMin;
    min = findMinimumValue( root );
    printf( "\nMin value: %d ", min );

    secMin = findSecondMinimumValue( root );
    printf( "\nSecond min value: %d ", secMin );

    freeTree( root );

    return 0;
}

int Push(Node **root, int value) {
    if ( *root == NULL ) {
        *root = ( Node * )malloc( sizeof( Node ) );
        ( *root )->val = value;
        ( *root )->left = NULL;
        ( *root )->right = NULL;
        return 1;
    } else if ( ( *root )->val > value ) {
        if ( Push( &( ( *root )->left ), value ) ) {
            if ( FB( *root ) > 1 ) {    //coloquei mais essa verificação no push
                if ( value < ( *root )->left->val ) {
                    RightRotation( root );
                } else {
                    LeftRotation( &( ( *root )->left ) );
                    RightRotation( root );
                }
            }
            return 1;
        }
    } else if ( ( *root )->val < value ) {
        if ( Push( &( ( *root )->right ), value )) {
            if ( FB( *root ) < -1 ) {   //coloquei mais essa verificação no push
                if ( value > ( *root )->right->val ) {
                    LeftRotation( root );
                } else {
                    RightRotation( &( ( *root )->right ) );
                    LeftRotation( root );
                }
            }
            return 1;
        } else
            return 0;
    } else
        return 0;
    return 0;
}

int FB( Node *root ) {
    if ( root == NULL )
        return 0;
    return Size( root->left ) - Size( root->right );
}

int Size( Node *root ) {
    if ( root == NULL )
        return 0;
    int left = Size( root->left );
    int right = Size( root->right );

    return ( left > right ? left : right ) + 1;
}

int Balance( Node **root ) {
    int fb = FB( *root );
    if ( fb > 1 )
        return LeftBalance( root );
    else if ( fb < -1 )
        return RightBalance( root );
    else
        return 0;
}

void LeftRotation( Node **root ) {
    Node *aux = ( *root )->right;
    ( *root )->right = aux->left;
    aux->left = ( *root );
    ( *root ) = aux;
}

void RightRotation( Node **root ) {
    Node *aux = ( *root )->left;
    ( *root )->left = aux->right;
    aux->right = ( *root );
    ( *root ) = aux;
}

//troquei os ifs do left balance e do right balance pra 1 e -1
int LeftBalance( Node **root ) {
    int fbl = FB ( ( *root )->left );
    if ( fbl > 1 ){
        RightRotation(root);
        return 1;
    }
    else if ( fbl < -1 ){     // Rotação Dupla Direita
        LeftRotation( &( ( *root)->right ) );
        RightRotation( root );
        return 1;
    }
    return 0;
}

int RightBalance( Node **root ) {
    int fbr = FB( ( *root )->right );
    if( fbr < -1 ){
        LeftRotation(root);
        return 0;
    }
    else if( fbr > 1 ){
        RightRotation( &( ( *root )->left ) );
        LeftRotation( root );
        return 0;
    }
   return 0;
}


void printTree( Node *root, int level ) {
    if ( root != NULL ) {
        printTree( root->right, level + 1 );

        for ( int i = 0; i < level; i++ ) {
            printf( "    " );
        }
        printf( "%d\n", root->val );

        printTree( root->left, level + 1 );
    }
}

void freeTree( Node *root ) {
    if ( root != NULL ) {
        freeTree( root->left );
        freeTree( root->right );
        free( root );  
    }
}

void Search ( Node *root, int *value, int *i ){
    if ( root == NULL )
        return;

    Search( root->left, value, i );
    value[( *i )++] = root->val;    //coloca num vetor

    Search( root->right, value, i );
}

int findSecondMinimumValue( Node* root ){
    if ( root == NULL )
        return -1;  //se nao eh nula
    int *value = ( int * )malloc( 100 * sizeof ( int ) );
    int i=0, temp=100, aux=-1;  //aux ja vai tem -1

    Search( root, value, &i );  //organiza a arvore em um vetor
    int size = i;   //diz qual o tamanho do vetor
    
    for( i = 0; i < size; i++ ){
        if ( value[i] < temp )
            temp = value [i];   //primeiro descobre qual o menor de todos
    }   

    for( i = 1; i < size; i++ ){
        if( ( value[i] > temp ) ){  //depois ve o primeiro que for menor que ele e menor que o resto
            aux = value[i];
            break;
        }
    }

    free ( value );
    return aux;

}

int findMinimumValue( Node* root ){
    if ( root == NULL )
        return -1;
    int *value = ( int * )malloc( 100 * sizeof ( int ) );
    int i=0, min=100;

    Search( root, value, &i );
    int size = i;
    
    for( i = 0; i < size; i++ ){
        if ( value[i] < min )
            min= value [i];
    }   
    free ( value );
    return min;

}