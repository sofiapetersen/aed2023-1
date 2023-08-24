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
Node *invertTree( Node *root );
void printTree( Node *root, int level );
void freeTree( Node *root );

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
    Node *inverted = invertTree( root );
    printf( "\nThe inverted tree:\n" );
    printTree( inverted, 0 );

    freeTree( root );

    return 0;
}

int Push( Node **root, int value ) {
    if ( *root == NULL ) {
        *root = ( Node * )malloc( sizeof( Node ) );
        ( *root )->val = value;
        ( *root )->left = NULL;
        ( *root )->right = NULL;
        return 1;
    } else if ( ( *root )->val > value ) {
        if ( Push( &( ( *root) ->left ), value ) ) {
            if ( Balance( root ) )
                return 0;
            else
                return 1;
        }
    } else if ( ( *root )->val < value ) {
        if ( Push( &( ( *root )->right ), value ) ) {
            if ( Balance( root ) )
                return 0;
            else
                return 1;
        } else
            return 0;
    } else
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

int LeftBalance( Node **root ) {
    int fbl = FB ( ( *root )->left );
    if ( fbl > 0 ){
        RightRotation(root);
        return 1;
    }
    else if ( fbl < 0 ){     // Rotação Dupla Direita
        LeftRotation( &( ( *root)->right ) );
        RightRotation( root );
        return 1;
    }
    return 0;
}

int RightBalance( Node **root ) {
    int fbr = FB( ( *root )->right );
    if( fbr < 0 ){
        LeftRotation(root);
        return 0;
    }
    else if( fbr > 0 ){
        RightRotation( &( ( *root )->left ) );
        LeftRotation( root );
        return 0;
    }
}


Node *invertTree( Node *root ) {
    if ( root == NULL )
        return NULL;

    Node *temp = root->left;
    root->left = invertTree( root->right );
    root->right = invertTree( temp );

    return root;
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