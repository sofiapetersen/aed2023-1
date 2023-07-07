/*vetor de 10 posicoes, colocar em ordem da esquerda pra direita*/

#include <stdio.h>
#include<stdlib.h>

void InsertionSort ( int array[], int size );

int main(){
    int size=10;
    int *array = ( int * )malloc( size * sizeof( int ) );
    array[0]  = 10;
    array[1] = 6;
    array[2] = 5;
    array[3] = 11;
    array[4] = 1;
    array[5] = 9;
    array[6] = 24;
    array[7] = 18;
    array[8] = 12;
    array[9] = 13;

    printf("Array:\n");
    for( int i=0; i<size; i++ ){
    printf( "%d\t", array[i] );
    }

    // até aqui foi pra allocar e preencher a array, dei um printf tbm pra enxergar como tava

    InsertionSort( array, size );

    printf( "\nArray after insertion sort:\n" );
    for( int i = 0; i<size; i++ ){
    printf( "%d\t", array[i] );
    }

    // depois passa por parametro pra funcao de insertionsort e da outro printf pra ver como ficou

    free(array);

return 0;
}

void InsertionSort ( int data[], int dataSize ){

    for( int j=1; j<dataSize; j++ ){    // percorre o vetor, começa no 1 pq se começar com 0 ele n pode ser comparado com nada do lado esquerdo
        int temp = data[j];     // temp recebe o data[j] pq ele vai (ou nao) ser substituido pelo numero do lado esquerdo
        int i = j-1;        
        while( ( i >= 0 ) && ( temp < data[i] ) ){  //esse while vai percorrer da direita pra esquerda, entao ele pega o data[i], 
                                                    //que no caso é que ta a esquerda do data[i] que nesse ponto virou temp, e compara compara os dois
            data[i+1] = data[i];        // entao se o data[i] (mais a esquerda) for maior que o temp, o data [i+1], que seria o proximo a direita recebe o que tava a esquerda
                                        // assim eles trocam de lugar
            i--;
        }

        data[i+1] = temp;
        // no final o data[i+1] vai ter o temp inicial que era o que ele tava comparando
    } 

}