/*vetor de 10 posicoes, colocar em ordem da esquerda pra direita*/

#include <stdio.h>
#include<stdlib.h>

void InsertionSort (int array[], int size);

int main(){
    int size=10;
    int *array = ( int * )malloc( size * sizeof( int ) );
    array[0]  = 3;
    array[1] = 6;
    array[2] = 5;
    array[3] = 11;
    array[4] = 1;
    array[5] = 9;
    array[6] = 24;
    array[7] = 18;
    array[8] = 12;
    array[9] = 13;

    for( int i=0; i<size; i++ ){
    printf("\n%d", array[i]);
    }

    printf( "\nAfter sort:\n" );

    InsertionSort(array, size);

return 0;
}

void InsertionSort (int data[], int dataSize){

    for( int j=1; j<dataSize; j++ ){
        int temp = data[j];
        int i = j-1;
        while( ( temp < data[i] ) && ( i >= 0 ) ){
            data[i+1] = data[i];
            i--;
        }

        data[i+1] = temp;
    } 

    for( int i = 0; i<dataSize; i++){
    printf("\n%d", data[i]);
    }

}