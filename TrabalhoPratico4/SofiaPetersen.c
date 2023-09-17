#include <stdlib.h>
#include <stdio.h>

typedef struct Interval {
    int start;
    int end;
} Position;

void sortMerge( Position data[], int left, int mid, int right );
void mergeSort( Position data[], int left, int right );
int** merge( int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes );

int main() {
    int intervalsSize;
    printf( "How many intervals? Type: " );
    scanf( "%d", &intervalsSize );
    int intervalsColSize = 2;   //sempre vai ser dois

    int **intervals = ( int ** )malloc( intervalsSize * sizeof( int * ) );
    for (int i = 0; i < intervalsSize; i++) {
        intervals[i] = ( int * )malloc( intervalsColSize * sizeof( int)  );   //cria uma array
    }

    for ( int i = 0; i < intervalsSize; i++ ) {
        printf("Type the interval %d (start end): ", i + 1);
        scanf( "%d %d", &intervals[i][0], &intervals[i][1] ); //preenche essa array com vetores
    }

    int returnSize;
    int *returnColumnSizes;

    int **mergedIntervals = merge( intervals, intervalsSize, &intervalsColSize, &returnSize, &returnColumnSizes );

    printf( "Output:\t" );
    printf( "[" );
    for ( int i = 0; i < returnSize; i++ ) {
        printf( "[%d, %d]", mergedIntervals[i][0], mergedIntervals[i][1] );
        if ( i < returnSize - 1 ) {
            printf( "," );
        }
    }
    printf( "]\n" );

    for ( int i = 0; i < intervalsSize; i++)  {
        free( intervals[i] );
    }
    free( intervals );

    for ( int i = 0; i < returnSize; i++ ) {
        free( mergedIntervals[i] );
    }
    free( mergedIntervals );
    free( returnColumnSizes );

    return 0;
}



 void sortMerge( Position data[], int left, int mid, int right ) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Position L[n1], R[n2];
    int i, j, k;

    for( i = 0; i < n1; i++ )
        L[i] = data[left+i];
    for( j = 0; j < n2; j++ )
        R[j] = data[mid + 1 +j];

    i = 0;  //indice inicial da primeira array
    j = 0;  //indice inicial da segunda array
    k = left;   //indice inicial da array mesclada

    while( i < n1 && j < n2 ){
        if ( L[i].start <= R[j].start ){
            data[k] = L[i];
            i++;
        } else{
            data[k] = R[j];
            j++;
        }
        k++;
    }
    while ( i < n1 ){
        data[k] = L[i];
        i++;
        k++;
    }
    while ( j < n2 ){
        data[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort( Position data[], int left, int right ){

    if ( left < right ){
        int mid = left + ( right - left )/2;

        mergeSort( data, left, mid );
        mergeSort( data, mid+1, right );

        sortMerge( data, left, mid, right );
    }
}

int** merge( int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes ) {
    if ( intervalsSize <= 0 ) {
        *returnSize = 0;
        return NULL;
    }

    Position *array = ( Position* )malloc( intervalsSize * sizeof( Position ) );

    for ( int i = 0; i < intervalsSize; i++ ) {
        array[i].start = intervals[i][0]; //preenche uma array temporaria que vai ser ordenada e dps mesclada
        array[i].end = intervals[i][1];
    }

    mergeSort( array, 0, intervalsSize - 1 );   //ordena essa array

    int** mergedIntervals = ( int** )malloc( intervalsSize * sizeof( int* ) );    //cria uma array que vai ser mesclada nos pontos que se sobrepoe
    *returnColumnSizes = ( int* )malloc( intervalsSize * sizeof( int ) );
    *returnSize = 0;

    int mergedStart = array[0].start;   //start recebe a primeira da primeira
    int mergedEnd = array[0].end;       //end recebe a primeira da primeira

    for ( int i = 1; i < intervalsSize; i++ ) {
        if ( array[i].start <= mergedEnd ) {  //ve se o proximo x do proximo vetor eh maior que o y do vetor inicial
            mergedEnd = ( array[i].end > mergedEnd ) ? array[i].end : mergedEnd; //se for maior, entao ele vai ser o y do vetor mesclado 
        } else {    //se nao for maior é pq n tem sobreposicao
            mergedIntervals[*returnSize] = (int*)malloc(2 * sizeof(int));       //aloca o intervalo mesclado
            mergedIntervals[*returnSize][0] = mergedStart;
            mergedIntervals[*returnSize][1] = mergedEnd;    //preenche o x,y, criando um novo vetor dentro do vetor
            ( *returnColumnSizes )[*returnSize] = 2;  //atualiza no 2 pq ja tem inicio e fim e é sempre 2
            ( *returnSize )++;    //incrementa o tamanho pra certificar que adicionou um intervalo

            mergedStart = array[i].start; //passa pro proximo intervalo
            mergedEnd = array[i].end;
        }
    }

    mergedIntervals[*returnSize] = ( int* )malloc( 2 * sizeof( int ) );   //pra garantir que tá adicionando o ultimo na lista
    mergedIntervals[*returnSize][0] = mergedStart;  //recebe os valores
    mergedIntervals[*returnSize][1] = mergedEnd;
    (*returnColumnSizes)[*returnSize] = 2;  //atualiza inicio e fim
    (*returnSize)++;    //incrementa pq adicionou um novo intervalo

    free( array );

    return mergedIntervals;
}




