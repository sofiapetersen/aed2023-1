#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectSort ( int data[], int n );     //seleção é bom pq ele sempre vai ter o mesmo tempo O(n2), ele sempre faz o mesmo processo, precisa percorrer todo o vetor
void quickSort ( int data[], int left, int right ); //é o mais rapido, mas pode ter tempos nao pre determinados pq ele tem melhor e pior caso, ele é instavel por causa da seleção do pivo, melhor caso é O(n log n) e o pior O(n2). A chance de cair no pior caso eh mt pequena, asism como de cair no melhor, mas como evita o pior, o resto tudo nao é tao ruim
void merge(int data[], int left, int mid, int right); // ele eh estavel, o tempo é sempre O(n log n)
void mergeSort(int arr[], int left, int right);

int main(){
    int n, option;

    printf("Type array size: ");
    scanf("%d", &n);

    int data[n];

    srand(time(0));

    for (int i = 0; i < n; i++) {
        data[i] = rand() % 100;
    }

    printf("\nChoose a sort:\n1- Select\n2- Quick\n3- Merge\nOption: ");
    scanf("%d", &option);
    if(option == 1){
    printf("Array:\n");
    for( int i=0; i<n; i++ ){
    printf( "%d\t", data[i] );
    }

    selectSort( data, n );

    printf( "\nArray after select sort:\n" );
    for( int i = 0; i<n; i++ ){
    printf( "%d\t", data[i] );
    }
    } else if (option == 2){

    printf("Array:\n");
    for( int i=0; i<n; i++ ){
    printf( "%d\t", data[i] );
    }


    quickSort( data, 0, n-1 );

    printf( "\nArray after quick sort:\n" );
    for( int i = 0; i<n; i++ )
    printf( "%d\t", data[i] );
    
    } else{

        printf("Array: \n");
        for( int i=0; i<n; i++ )
            printf( "%d\t", data[i] );
        

    mergeSort(data, 0, n - 1);

    printf( "\nArray after quick sort:\n" );
    for( int i = 0; i<n; i++ )
        printf( "%d\t", data[i] );
    
    }


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