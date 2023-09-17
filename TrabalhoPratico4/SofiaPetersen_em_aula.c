/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

 void sortMerge(int data[], int left, int mid, int right) {
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

        sortMerge(data, left, mid, right);
    }
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    int *array = (int *)malloc(sizeof(int)*100);
    int *columnsSize = (int*)malloc(sizeof(int));
    int *vectorX = (int *)malloc(sizeof(int)*100);
    int *vectorY = (int *)malloc(sizeof(int)*100);
    
    for(int i = 0; i <intervalsSize; i++){
        vectorX[intervalsColSize[i]] = intervals[i];
        for(int j = 1; j < intervalsSize; j++){
            vectorY[intervalsColSize[j]] = intervals[j];
        }
    }

    return array;
}


/*a minha ideia inicial era dar merge a cada dois vetores e ver se o primeiro é do primeiro vetor e o ultimo é do segundo vetor, se sim, então é pq tao no mesmo intervalo entao pegar o primeiro e ultimo e colocar na array de retorno
mas to com dificuldade de conseguir acessar cada indice do vetor intervals, realmente nunca tinha trabalhado com vetor de vetores*/