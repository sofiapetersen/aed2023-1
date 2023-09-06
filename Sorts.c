#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void selectSort ( int data[], int n );     //seleção é bom pq ele sempre vai ter o mesmo tempo O(n2), ele sempre faz o mesmo processo, precisa percorrer todo o vetor
void quickSort ( int data[], int left, int right ); //é o mais rapido, mas pode ter tempos nao pre determinados pq ele tem melhor e pior caso, ele é instavel por causa da seleção do pivo, melhor caso é O(n log n) e o pior O(n2). A chance de cair no pior caso eh mt pequena, asism como de cair no melhor, mas como evita o pior, o resto tudo nao é tao ruim
void merge(int data[], int left, int mid, int right); // ele eh estavel, o tempo é sempre O(n log n)
void mergeSort(int arr[], int left, int right);
void insertionSort ( int data[], int dataSize );

int main(){

    struct timeval begin, end; // variáveis de tempo

    int n, option;

    n = 10;

    int *data = (int *)malloc(n * sizeof(int));

    srand(time(0));

    for (int i = 0; i < n; i++) 
        data[i] = rand() % 100;
    

    printf("\nChoose a sort:\n1- Select\n2- Quick\n3- Merge\n4- Insertion\nOption: ");
    scanf("%d", &option);

    // gettimeofday() antes de iniciar o algoritmo
    gettimeofday(&begin, NULL);


    if(option == 1){
        // printf("Array:\n");
        // for( int i=0; i<n; i++ )
        //     printf( "%d\t", data[i] );
    
        selectSort( data, n );

        // printf( "\nArray after select sort:\n" );
        // for( int i = 0; i<n; i++ )
        //     printf( "%d\t", data[i] );
        
    } else if (option == 2){

        // printf("Array:\n");
        // for( int i=0; i<n; i++ )
        //     printf( "%d\t", data[i] );
        
        quickSort( data, 0, n-1 );

        // printf( "\nArray after quick sort:\n" );
        // for( int i = 0; i<n; i++ )
        //     printf( "%d\t", data[i] );
    
    } else if (option == 3) {

        // printf("Array: \n");
        // for( int i=0; i<n; i++ )
        //     printf( "%d\t", data[i] );
        

        mergeSort(data, 0, n - 1);

        // printf( "\nArray after quick sort:\n" );
        // for( int i = 0; i<n; i++ )
        //     printf( "%d\t", data[i] );
    
    } else {
        // printf("Array:\n");
        // for( int i=0; i<n; i++ )
        //     printf( "%d\t", data[i] );
    
        insertionSort( data, n );

        // printf( "\nArray after insertion sort:\n" );
        // for( int i = 0; i<n; i++ )
        //     printf( "%d\t", data[i] );
    }

    // gettimeofday() novamente após a execução do algoritmo
    gettimeofday(&end, NULL);

    // calcula o tempo decorrido em segundos com microssegundos
    double elapsed_time = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1000000.0;

    printf("\nElapsed time: %.10f seconds\n", elapsed_time);
    
    free(data);

    

return 0;
}

void selectSort ( int data[], int n ){
    int min, temp, i, j, min_id;

    for(i = 0; i < n-1; i++){
        min = data[i];
        for(j = i+1; j < n; j++)
            if(data[j] < min){
                min = data[j];
                min_id = j;
            }
        temp = data[i];
        data[i] = data[min_id];
        data[min_id] = temp;
        min_id = i+1;
    }

}

void quickSort ( int data[], int left, int right ){
    int mid, temp, i, j;
    i = left;
    j = right;
    mid = data[(left+right)/2];

    do{
        while (data[i] < mid)
            i++;
        
        while(mid < data[j])
            j--;
        if (i <= j){
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    
    if (left < j)
        quickSort(data, left, j);
    if (i < right)
        quickSort(data, i, right);
}

void merge(int data[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2], i, j, k;

    for(i = 0; i < n1; i++)
        L[i] = data[left+i];
    for(j = 0; j < n2; j++)
        R[j] = data[mid + 1 +j];

    i = 0;  //indice inicial da primeira array
    j = 0;  //indice inicial da segunda array
    k = left;   //indice inicial da array mesclada

    while(i < n1 && j < n2){
        if (L[i] <= R[j]){
            data[k] = L[i];
            i++;
        } else{
            data[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        data[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        data[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int data[], int left, int right){
    if ( left < right ){
        int mid = left + (right - left)/2;

        mergeSort(data, left, mid);
        mergeSort(data, mid+1, right);

        merge(data, left, mid, right);
    }
}

void insertionSort ( int data[], int dataSize ){

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