#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    int color;  // 0 preto || 1 vermelho
    struct Node *parent;
    struct Node *right;
    struct Node *left;
} node;

node *uncle(node *n);
node *grandparent(node *n);
void insertCase1(node **root, node *n);
void insertCase2(node **root, node *n);
void insertCase3(node **root, node *n);
void insertCase4(node **root, node *n);
void insertCase5(node **root, node *n);
void RSE(node *root, node *x);
void RSD(node *root, node *y);
void printTree(node *root, int level);
void freeTree(node *root);

int main() {
    int nodes;
    node *root = NULL;

    printf("Nodes: ");
    scanf("%d", &nodes);
    srand(time(0));

    for (int i = 0; i < nodes; i++) {
        node *new = (node *)malloc(sizeof(node));
        new->data = rand() % 100;
        new->color = 1;  // Novo nó sempre é vermelho
        new->right = new->left = new->parent = NULL;

        if (root == NULL) {
            root = new;
            root->color = 0;
        } else {
            insertCase1(&root, new);
        }
        printf("Insertion complete\n");
        printTree(root, 0);
    }

    freeTree(root);  // Liberar memória alocada pela árvore

    return 0;
}

node *grandparent(node *n) {
    if (n != NULL && n->parent != NULL)
        return n->parent->parent;
    else
        return NULL;
}

node *uncle(node *n) {
    node *g = grandparent(n);
    if (g == NULL)
        return NULL;  // Se não tem grandparent, não tem uncle
    if (n->parent == g->left)
        return g->right;
    else
        return g->left;
}

void insertCase1(node **root, node *n) {
    if (n->parent == NULL) {
        n->color = 0;
        *root = n;
    } else
        insertCase2(root, n);
}

void insertCase2(node **root, node *n) {
    if (n->parent->color == 0)
        return;
    else
        insertCase3(root, n);
}

void insertCase3(node **root, node *n) {
    node *g = grandparent(n);
    node *u = uncle(n);
    if (u != NULL && u->color == 1) {
        n->parent->color = 0;
        u->color = 0;
        g->color = 1;
        insertCase1(root, g);
    } else
        insertCase4(root, n);
}

void insertCase4(node **root, node *n) {
    node *g = grandparent(n);
    if (n == n->parent->right && n->parent == g->left) {
        RSE(*root, n->parent);
        n = n->left;
    } else if (n == n->parent->left && n->parent == g->right) {
        RSD(*root, n->parent);
        n = n->right;
    }
    insertCase5(root, n);
}

void insertCase5(node **root, node *n) {
    node *g = grandparent(n);
    n->parent->color = 0;
    g->color = 1;
    if (n == n->parent->left && n->parent == g->left)
        RSD(*root, g);
    else
        RSE(*root, g);
}

void RSE(node *root, node *x) {
    node *aux = x->right;
    x->right = aux->left;
    if (aux->left != NULL)
        aux->left->parent = x;
    aux->parent = x->parent;
    if (x->parent == NULL)
        root = aux;
    else if (x == x->parent->left)
        x->parent->left = aux;
    else
        x->parent->right = aux;
    aux->left = x;
    x->parent = aux;
}

void RSD(node *root, node *y) {
    node *aux = y->left;
    y->left = aux->right;
    if (aux->right != NULL)
        aux->right->parent = y;
    aux->parent = y->parent;
    if (y->parent == NULL)
        root = aux;
    else if (y == y->parent->left)
        y->parent->left = aux;
    else
        y->parent->right = aux;
    aux->right = y;
    y->parent = aux;
}

void printTree(node *root, int level) {
    if (root != NULL) {
        printTree(root->right, level + 1);
        for (int i = 0; i < level; i++) printf("    ");
        printf("(%d,%c)\n", root->data, root->color == 0 ? 'B' : 'R');
        printTree(root->left, level + 1);
    }
}

void freeTree(node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
