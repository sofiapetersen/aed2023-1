#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
	struct matrix *right;
	struct matrix *below;
	int rows;
	int column;
	float info;
}Matrix;

Matrix *matrix_create( void );
void matrix_print(Matrix* head);

int main( void ) {

    Matrix *A = matrix_create();
    printf( "%.2f\n", A->right->below->info);
    printf( "%.2f\n", A->below->below->right->right->info);
    matrix_print(A);
    return 0;
}


Matrix *matrix_create(void) {
    int i, j, m, n, flag;
    char c;
    float value;

    printf("\nEnter the number of rows and columns: ");
    scanf("%d %d", &m, &n);
    getchar();

    Matrix *head = (Matrix *)malloc(sizeof(Matrix));

    head->rows = -1;
    head->column = -1;
    head->right = NULL;
    head->below = NULL;

    Matrix *head_row[m], *head_col[n];

    for (i = 0; i < m; i++) {
        head_row[i] = (Matrix *)malloc(sizeof(Matrix));
    }

    for (i = 0; i < n; i++) {
        head_col[i] = (Matrix *)malloc(sizeof(Matrix));
    }

    head->right = head_col[0];
    head->below = head_row[0];

    for (i = 0; i < m - 1; i++) {
        head_row[i]->below = head_row[i+1];
        head_row[i]->right = head_row[i];
    }
    head_row[i]->right = head_row[i];
    head_row[i]->below = head;

    for (i = 0; i < n - 1; i++) {
        head_col[i]->right = head_col[i+1];
        head_col[i]->below = head_col[i];
    }
    head_col[i]->right = head;
    head_col[i]->below = head_col[i];

    for (;;) {
        flag = 0;
        do {
            if (flag == 1)
                printf("\nInvalid value, insert again!!");

            printf("\nEnter row, column, value: ");
            scanf("%d %d %f", &i, &j, &value);
            flag = 1;
            getchar();
        } while (i > m || j > n || i < 1 || j < 1);

        if (i == 0 || j == 0 || value == 0)
            break;

        Matrix *new = (Matrix *)malloc(sizeof(Matrix));
        new->rows = i;
        new->column = j;
        new->info = value;

        Matrix *p, *q;
        for (p = head_row[i-1]; p->right != head_row[i-1] && p->right->column < j; p = p->right);
        for (q = head_col[j-1]; q->below != head_col[j-1] && q->below->rows < i; q = q->below);

        new->right = p->right;
        p->right = new;
        new->below = q->below;
        q->below = new;

        printf("\nDo you want to insert another cell? (Y/N): ");
        scanf(" %c", &c);
        if (c == 'N' || c == 'n')
            break;
    }
    return head;
}

void matrix_print(Matrix* head) {
    Matrix* currentRow = head->below;

    while (currentRow != head) {
        Matrix* currentCell = currentRow->right;

        while (currentCell != currentRow) {
            printf("(%d, %d): %.2f   ", currentCell->rows, currentCell->column, currentCell->info);
            currentCell = currentCell->right;
        }

        printf("\n");
        currentRow = currentRow->below;
    }
}