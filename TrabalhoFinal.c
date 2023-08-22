// Mostre o desempenho em termos de memória e tempo de execução usando a versão usando listas e a versão força bruta. ?

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct matrix {
	struct matrix *right;
	struct matrix *below;
	int row;
	int column;
	float info;
}Matrix;

Matrix *matrix_create( void );//-------------------------------->Completo graças a Deus
void matrix_print( Matrix *m );//------------------------------->Completo finalmente
void matrix_destroy( Matrix *m );//----------------------------->Completo
void matrix_setelem( Matrix *m, int x, int y, float elem );//--->Completo
float matrix_getelem( Matrix *m, int x, int y );//-------------->Completo
Matrix *matrix_add( Matrix *m, Matrix *n );//------------------->Completo
Matrix *matrix_multiply( Matrix *m, Matrix *n );//-------------->Corrigido e Completo
Matrix *matrix_transpose( Matrix *m );//------------------------>Completo
Matrix *heads_create( int x, int y );//------------------------->Fiz a mais para poupar tempo e linhas de código
int compare_to( int x, int y );
Matrix *matrix_create_random( unsigned int m );//--------------->Completo

int main( void )
{
    Matrix *A = matrix_create();
    matrix_print( A );
    Matrix *B = matrix_create(); 
    matrix_print( B );
    Matrix *C = matrix_add( A, B ); 
    matrix_print( C );
    matrix_destroy( C );
    C = matrix_multiply( A, B ); 
    matrix_print( C );
    matrix_destroy( C );
    C = matrix_transpose( A ); 
    matrix_print( C );
    matrix_destroy( C );
    matrix_destroy( A );
    matrix_destroy( B );

    printf( "Create a random square matrix, insert rows and columns: " );
    unsigned int random;
    scanf( "%u", &random );
    Matrix *D = matrix_create_random( random );
    matrix_print( D );
    matrix_destroy( D );
    return 0;

}

Matrix *heads_create( int x, int y )
{
    int i;
    Matrix *head = ( Matrix * )malloc( sizeof( Matrix ) );//------>Cria a cabeça principal

    head->row = -1;
    head->column = -1;
    head->right = NULL;
    head->below = NULL;

    Matrix *head_row[x], *head_col[y];

    for ( i = 0; i < x; i++ )//----------------------------------->Cria a cabeça de cada uma das linhas baseado na entrada 'm'
    {
        head_row[i] = ( Matrix * )malloc( sizeof( Matrix ) );
        head_row[i]->right = head_row[i];//----------------------->Faz a cabeça de cada linha apontar para si própria
        head_row[i]->below = NULL;
        head_row[i]->row = -1;
    }

    for ( i = 0; i < y; i++ )//----------------------------------->Cria a cabeça de cada uma das colunas baseado na entrada 'n'
    {
        head_col[i] = ( Matrix * )malloc( sizeof( Matrix ) );
        head_col[i]->below = head_col[i];//----------------------->Faz a cabeça de cada coluna apontar para si própria
        head_col[i]->right = NULL;
        head_col[i]->column = -1;
    }

    head->right = head_col[0];//---------------------------------->Faz a cabeça principal apontar para a cabeça que repesenta a primeira coluna
    head->below = head_row[0];//---------------------------------->Faz a cabeça principal apontar para a cabeça que repesenta a primeira linha

    for ( i = 0; i < x - 1; i++ )//------------------------------->Faz a cabeça de cada linha apontar para a cabeça da linha de baixo
        head_row[i]->below = head_row[i+1];

    head_row[i]->below = head;//---------------------------------->Faz a última linha apontar para a cabeça

    for ( i = 0; i < y - 1; i++ )//------------------------------->Faz a cabeça de cada coluna apontar para a cabeça da coluna do lado
        head_col[i]->right = head_col[i+1];

    head_col[i]->right = head;//---------------------------------->Faz a última coluna apontar para a cabeça

    return head;
}

void matrix_setelem( Matrix* m, int x, int y, float elem )
{
    int nRows = 1, nCols = 1;
    Matrix *new = ( Matrix * )malloc( sizeof( Matrix ) );
    new->row = x;
    new->column = y;
    new->info = elem;

    Matrix *p, *q, *r, *s;
    for ( r = m->right; r != m && y != nCols; r = r->right, nCols++ );//-------->Conta a quantidade de Colunas
    for ( s = m->below; s != m && x != nRows; s = s->below, nRows++ );//-------->Conta a quantidade de Linhas

    for ( q = r; q->below != r && q->below->row < x; q = q->below );//---------->Encontra a linha onde a célula será inserida
    for ( p = s; p->right != s && p->right->column < y; p = p->right );//------->Encontra a coluna onde a célula será inserida
    

    new->right = p->right;
    p->right = new;
    new->below = q->below;
    q->below = new;

    if ( ( p->right->right->row == x && p->right->right->column == y ) )//------>Se já houver alguma célula na mesma posição a antiga é desalocada, dando espaço para a nova
    {
        Matrix *temp = p->right->right;
        new->right = temp->right;
        temp->right = NULL;
        new->below = temp->below;
        temp->below = NULL;
        free( temp );
    }
}

Matrix *matrix_create( void ) {
    int i, j, m, n;
    float value;

    printf( "\nEnter the number of rows and columns: " );
    scanf( "%d %d", &m, &n );
    getchar();

    Matrix *head = heads_create( m, n );    //----->Cria as cabeças da matriz

    while (1)
    {
         
        printf( "\nEnter row, column, value (or 0 to exit): " );
        scanf( "%d", &i );

        if ( ( i == 0 ) )      //------------------------------->Primeiro ele confere se o i não é 0, se for 0 quebra, se nao continua
            break;

        scanf( "%d %f", &j, &value );   //----------------------->Pra inserir os proximos valores
        
        if ( i > m || j > n || i < 1 || j < 1 ) //--------------->Se for maior que o numero de colunas/linhas ou se for menor que 1 ele solicita de novo
        {
            printf( "\nInvalid value, insert again!!" );
            continue;
        }

        matrix_setelem( head, i, j, value );//-------------------->Cria uma nova célula a partir da função 'matrix_setelem'
    }

        return head;
    }

void matrix_print( Matrix *m ) {
    Matrix *currentRow = NULL;
    int nRows = 1, nCols = 1;

    for ( currentRow = m->below; currentRow->below != m; currentRow = currentRow->below, nRows++ );//->Conta a quantidade de linhas
    for ( currentRow = m->right; currentRow->right != m; currentRow = currentRow->right, nCols++ );//->Conta a quantidade de colunas

    int curRow, curCol;

    float **matrix = ( float ** )malloc( nRows * sizeof( float * ) );//--->Cria uma matriz de nRows x nCols dinamicamente
    for ( curRow = 0; curRow < nRows; curRow++ )
    {
        matrix[curRow] = ( float * )malloc( nCols * sizeof( float ) );
    }

    for ( curRow = 0; curRow < nRows; curRow++ )//--->Inicializa todos o elementos da matriz em '0'
        for ( curCol = 0; curCol < nCols; curCol++ )
            matrix[curRow][curCol] = 0;

    currentRow = m->below;//------>CurrentRow recebe a cabeça da primeira linha

    while ( currentRow != m )//--->Reepete enquanto o currentRow não voltar para a cabeça principal
    {
        Matrix *currentCell = currentRow->right;//-->CurrentCell recebe a primeira célula da linha

        while ( currentCell != currentRow )
        {
            matrix[currentCell->row - 1][currentCell->column - 1] = currentCell->info;//-->A matriz criada recebe o valor que está na mesma posição da matriz esparsa
            currentCell = currentCell->right;//-->Vai para a próxima célula na mesma linha
        }

        currentRow = currentRow->below;//--->Terminada a linha, pula para a próxima
    }

    
    for ( curRow = 0; curRow < nRows; curRow++ )//->Printa a matriz esparsa com os '0's nas posições vazias
    {
        for ( curCol = 0; curCol < nCols; curCol++ )
        {
            if ( matrix[curRow][curCol] < 10 ) {
                printf( "(%d, %d): %.2f   ", ( curRow + 1 ), ( curCol + 1 ), matrix[curRow][curCol] );
            } else {
                printf( "(%d, %d): %.2f  ", ( curRow + 1 ), ( curCol + 1 ), matrix[curRow][curCol] );
            }
        }
        printf( "\n" );//--->Pula uma linha depois de percorrer o curCol
    }
    printf( "\n\n" );

    
    for (curRow = 0; curRow < nRows; curRow++)//-->Libera a memória alocada para a matriz
        free(matrix[curRow]);
    free(matrix);
}


void matrix_destroy( Matrix *m ) {
    Matrix *currentRow = m->below;//-------------------->Inicializa o currentRow com a primeira linha da matriz

    while ( currentRow != m )//------------------------->Repete enquanto currentRow não retornar para a cabeça principal
    {
        Matrix *currentCell = currentRow->right;//------>CurrentCell recebe a primeira célula daquela linha

        while ( currentCell != currentRow )//----------->Repete enquanto o currentCell não retornar para a cabeça da linha atual
        {
            Matrix *temp = currentCell;
            temp->below = temp;
            currentCell = currentCell->right;
            currentRow->right = currentCell;
            free( temp );//----------------------------->Libera um a um todas as células daquela linha
        }

        Matrix *tempRow = currentRow;
        currentRow = currentRow->below;//--------------->currentRow recebe a cabeça da próxima linha
        free( tempRow );//------------------------------>Libera a cabeça da linha na qual todas as células já foram apagadas
    }

    Matrix *currentCol = m->right;//-------------------->Inicializa o currentCol com a primeira coluna da matriz

    while ( currentCol != m )//------------------------->Libera as cabeças da colunas da matriz
    {
        Matrix *tempCol = currentCol;
        currentCol = currentCol->right;
        free ( tempCol );
    }

    free( m );//---------------------------------------->Libera a cabeça principal da matriz

    printf("Matrix destroyed\n");
}

float matrix_getelem( Matrix *m, int x, int y )
{
    Matrix *currentRow = NULL;
    int nRows = 1, nCols = 1;

    for ( currentRow = m->below; currentRow->below != m; currentRow = currentRow->below, nRows++ );//->Conta a quantidade de linhas
    for ( currentRow = m->right; currentRow->right != m; currentRow = currentRow->right, nCols++ );//->Conta a quantidade de colunas

    int curRow, curCol;
    float matrix[nRows][nCols];//--------------------------------------------------------------------->Cria uma matriz de nRows x nCols

    for ( curRow = 0; curRow <= nRows; curRow++ )//--------------------------------------------------->Inicializa todos o elementos da matriz em '0'
        for ( curCol = 0; curCol <= nCols; curCol++ )
            matrix[curRow][curCol] = 0;

    currentRow = m->below;//-------------------------------------------------------------------------->CurrentRow recebe a cabeça da primeira linha

    while ( currentRow != m )//----------------------------------------------------------------------->Reepete enquanto o currentRow não voltar para a cabeça principal
    {
        Matrix *currentCell = currentRow->right;//---------------------------------------------------->CurrentCell recebe a primeira célula da linha
        
        while ( currentCell != currentRow )//--------------------------------------------------------->Repete enquanto o currentCell não voltar para a cabeça da linha
        {
            matrix[currentCell->row - 1][currentCell->column - 1] = currentCell->info;//-------------->A matriz criada recebe o valor que está na mesma posição da matriz esparsa
            currentCell = currentCell->right;//------------------------------------------------------->Vai para a próxima célula na mesma linha
        }

        currentRow = currentRow->below;//------------------------------------------------------------->Terminada a linha, pula para a próxima
    }

    return matrix[x - 1][y - 1];//-------------------------------------------------------------------->Retorna o valor da célula na posição desejada
}

int compare_to( int x, int y )
{
    return x > y ? x : y;
}

Matrix *matrix_add( Matrix *m, Matrix *n )
{
    Matrix *currentRow = NULL;
    int nRowsM = 1, nColsM = 1, nRowsN = 1, nColsN = 1;

    for ( currentRow = m->below; currentRow->below != m; currentRow = currentRow->below, nRowsM++ );//->Conta a quantidade de linhas da matriz m
    for ( currentRow = m->right; currentRow->right != m; currentRow = currentRow->right, nColsM++ );//->Conta a quantidade de colunas da matriz m

    for ( currentRow = n->below; currentRow->below != n; currentRow = currentRow->below, nRowsN++ );//->Conta a quantidade de linhas da matriz n
    for ( currentRow = n->right; currentRow->right != n; currentRow = currentRow->right, nColsN++ );//->Conta a quantidade de colunas da matriz n


    int curRow, curCol, Rows = compare_to( nRowsM, nRowsN ), Cols = compare_to( nColsM, nColsN );

    float **matrix = ( float ** )malloc( Rows * sizeof( float * ) );//--->Cria uma matriz de nRows x nCols dinamicamente
    for ( curRow = 0; curRow < Rows; curRow++ )
    {
        matrix[curRow] = ( float * )malloc( Cols * sizeof( float ) );
    }

    for ( curRow = 0; curRow < Rows; curRow++ )//--->Inicializa todos o elementos da matriz em '0'
        for ( curCol = 0; curCol < Cols; curCol++ )
            matrix[curRow][curCol] = 0;

    currentRow = m->below;//------>CurrentRow recebe a cabeça da primeira linha
    
    while ( currentRow != m )//------------->Repete enquanto o currentRow não voltar para a cabeça principal
    {
        Matrix *currentCell = currentRow->right;//-------->CurrentCell recebe a primeira célula da linha
        
        while ( currentCell != currentRow )//------------->Repete enquanto o currentCell não voltar para a cabeça da linha
        {
            matrix[currentCell->row - 1][currentCell->column - 1] = currentCell->info;//->A matriz criada recebe o valor que está na mesma posição da matriz esparsa
            currentCell = currentCell->right;//------------->Vai para a próxima célula na mesma linha
        }

        currentRow = currentRow->below;//------------->Terminada a linha, pula para a próxima
    }

    currentRow = n->below;//-------->CurrentRow recebe a cabeça da primeira linha da matriz n

    while ( currentRow != n )//----->Faz a mesma coisa, agora na matriz n
    {
        Matrix *currentCell = currentRow->right;
        
        while ( currentCell != currentRow )
        {
            matrix[currentCell->row - 1][currentCell->column - 1] += currentCell->info;//--->Soma com o valor que estiver nessa posição da matriz
            currentCell = currentCell->right;
        }

        currentRow = currentRow->below;
    }

    Matrix *head = heads_create( Rows, Cols );//------>Cria as cabeças da nova matriz

    for ( curRow = 0; curRow < Rows; curRow++ )
    {
        for ( curCol = 0; curCol < Cols; curCol++ )
        {
            if ( matrix[curRow][curCol] != 0 )//---------->Se o valor da matriz atual for diferente de '0' ele será inserido da matriz de retorno
                matrix_setelem( head, ( curRow + 1), ( curCol + 1 ), matrix[curRow][curCol] );
        }
    }

    for (curRow = 0; curRow < Rows; curRow++)//-->Libera a memória alocada para a matriz
        free(matrix[curRow]);
    free(matrix);

    return head;
}

Matrix *matrix_multiply( Matrix *m, Matrix *n )
{
    Matrix *currentRow = NULL;
    int nRowsM = 1, nColsM = 1, nRowsN = 1, nColsN = 1;

    for ( currentRow = m->below; currentRow->below != m; currentRow = currentRow->below, nRowsM++ );//->Conta a quantidade de linhas da matriz m
    for ( currentRow = m->right; currentRow->right != m; currentRow = currentRow->right, nColsM++ );//->Conta a quantidade de colunas da matriz m

    for ( currentRow = n->below; currentRow->below != n; currentRow = currentRow->below, nRowsN++ );//->Conta a quantidade de linhas da matriz n
    for ( currentRow = n->right; currentRow->right != n; currentRow = currentRow->right, nColsN++ );//->Conta a quantidade de colunas da matriz n


    int curRow, curCol, Rows = compare_to( nRowsM, nRowsN ), Cols = compare_to( nColsM, nColsN );;

    float **matrixM = ( float ** )malloc( Rows * sizeof( float * ) );//--->Cria uma matriz M de nRows x nCols dinamicamente
    float **matrixN = ( float ** )malloc( Rows * sizeof( float * ) );//--->Cria uma matriz N de nRows x nCols dinamicamente
    
    for ( curRow = 0; curRow < Rows; curRow++ )
    {
        matrixM[curRow] = ( float * )malloc( Cols * sizeof( float ) );
        matrixN[curRow] = ( float * )malloc( Cols * sizeof( float ) );
    }

    for ( curRow = 0; curRow < Rows; curRow++ )//--->Inicializa todos o elementos das matrizes em '0'
        for ( curCol = 0; curCol < Cols; curCol++ ){
            matrixM[curRow][curCol] = 0;
            matrixN[curRow][curCol] = 0;
        }

    currentRow = m->below;//------>CurrentRow recebe a cabeça da primeira linha

    while ( currentRow != m )//------------->Repete enquanto o currentRow não voltar para a cabeça principal
    {
        Matrix *currentCell = currentRow->right;//-------->CurrentCell recebe a primeira célula da linha
        
        while ( currentCell != currentRow )//------------->Repete enquanto o currentCell não voltar para a cabeça da linha
        {
            matrixM[currentCell->row - 1][currentCell->column - 1] = currentCell->info;//->A matriz criada recebe o valor que está na mesma posição da matriz esparsa
            currentCell = currentCell->right;//------------->Vai para a próxima célula na mesma linha
        }

        currentRow = currentRow->below;//------------->Terminada a linha, pula para a próxima
    }

    currentRow = n->below;//-------->CurrentRow recebe a cabeça da primeira linha da matriz n

    while ( currentRow != n )//----->Faz a mesma coisa, agora na matriz n
    {
        Matrix *currentCell = currentRow->right;
        
        while ( currentCell != currentRow )
        {
            matrixN[currentCell->row - 1][currentCell->column - 1] = ( matrixM[currentCell->row - 1][currentCell->column - 1] ) * currentCell->info;//--->Multiplica pelo valor que estiver nessa posição da matriz 'm'
            currentCell = currentCell->right;
        }

        currentRow = currentRow->below;
    }

    Matrix *head = heads_create( Rows, Cols );//------>Cria as cabeças da nova matriz

    for ( curRow = 0; curRow < Rows; curRow++ )
    {
        for ( curCol = 0; curCol < Cols; curCol++ )
        {
            if ( matrixN[curRow][curCol] != 0 )//---------->Se o valor da matriz atual for diferente de '0' ele será inserido da matriz de retorno
                matrix_setelem( head, ( curRow + 1), ( curCol + 1 ), matrixN[curRow][curCol] );
        }
    }

    for (curRow = 0; curRow < Rows; curRow++)//-->Libera a memória alocada para a matriz M
        free(matrixM[curRow]);
    free(matrixM);

    for (curRow = 0; curRow < Rows; curRow++)//-->Libera a memória alocada para a matriz N
        free(matrixN[curRow]);
    free(matrixN);


    return head;
}

Matrix *matrix_transpose( Matrix *m )
{
    Matrix *currentRow = NULL;
    int nRows = 1, nCols = 1;

    for ( currentRow = m->below; currentRow->below != m; currentRow = currentRow->below, nRows++ );//->Conta a quantidade de linhas da matriz
    for ( currentRow = m->right; currentRow->right != m; currentRow = currentRow->right, nCols++ );//->Conta a quantidade de colunas da matriz

    Matrix* head = heads_create( nCols, nRows ); //--------------------------------------------------->Cria uma nova matriz com as dimensões ao contrario

    currentRow = m->below; //------------------------------------------------------------------------->Recebe a cabeça da primeira linha

    while ( currentRow != m ){  //-------------------------------------------------------------------->Percorre até voltar pra cabeça                                                                                                       
        Matrix *currentCell = currentRow->right;  //-------------------------------------------------->Recebe a primeira celula da linha
            
            while ( currentCell != currentRow ){   //-------------------------------------------------->Percorre até voltar pra cabeça da linha
                matrix_setelem( head, currentCell->column, currentCell->row, currentCell->info ); //----->Insere o valor na transposta, com as posicoes inversas por ser transposta
                currentCell = currentCell->right;   //------------------------------------------------->Passa pra proxima linha
            }
        currentRow = currentRow->below;   //--------------------------------------------------------->Depois de passar por todas as colunas da linha, passa pra proxima linha
    }

    return head;
}

Matrix *matrix_create_random( unsigned int m )
{
    int i, j, value, total = m*m, filled = 0;
    Matrix *head = heads_create( m, m );    //----->Cria as cabeças da matriz
    srand( time ( 0 ) );

    while ( filled < total )
    {
         
        i = rand() % m;
        j = rand() % m;
        value = rand() % 200;

        matrix_setelem( head, i+1, j+1, value );//-------------------->Cria uma nova célula a partir da função 'matrix_setelem'
        filled++;
    }

        return head;
}