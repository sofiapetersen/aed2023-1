#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n);
void quickSort ( int data[], int left, int right );

int main() {

    int m;
    int n;

    printf("m: ");
    scanf("%d", &m);

    printf("n: ");
    scanf("%d", &n);

    int nums1[m+n];
    int nums2[n];

    srand(time(0));

    for (int i = 0; i < m; i++) 
        nums1[i] = rand() % 30;

    quickSort(nums1, 0, m-1);
    
    for (int i = 0; i < n; i++) 
        nums2[i] = rand() % 30;
    
    quickSort(nums2, 0, n-1);

    merge(nums1, m+n, m, nums2, n, n);

    printf("Resultado: [");
    for (int i = 0; i < m + n; i++) {
        printf("%d ", nums1[i]);
        if (i < m + n - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int index1 = m - 1; //indice do ultimo valido em nums1
    int index2 = n - 1; //indice do ultimo valido em nums2
    int index_merged = m + n - 1;   //indice do ultimo valido no vetor mesclado
    
    while (index1 >= 0 && index2 >= 0) {
        if (nums1[index1] > nums2[index2]) {
            nums1[index_merged] = nums1[index1];    //se o numero em nums1 for maior que o de nums2, coloca ele no vetor (de tras pra frente)
            index1--;   //e decremeta uma posicao
        } else {
            nums1[index_merged] = nums2[index2];    //se o nums2 for maior entao coloca ele
            index2--;   //e decrementa uma posicao do nums2
        }
        index_merged--; //e toda vez passa pro proximo indice decrementando
    }
    
    while (index2 >= 0) {   //caso ainda tenham numeros do nums2 que ainda nao foram colocados
        nums1[index_merged] = nums2[index2];
        index2--;
        index_merged--;
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