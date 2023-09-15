#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort ( int data[], int left, int right );
int missingNumber(int* nums, int numsSize);

int main() {

    int nums[] = {0,1};
    int size = sizeof(nums) / sizeof(nums[0]);
    quickSort(nums, 0, size);
    
    int number = missingNumber(nums, size);

    printf("Missing: %d", number);

    return 0;
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

int missingNumber(int* nums, int numsSize){
    int i;
    for(i = 0; i < numsSize; i++){
        if(nums[i] != i)
        return i;
    }

    return numsSize;
}



// int missingNumber(int* nums, int numsSize){

//     int min, temp, i, j, min_id;

//     for(i = 0; i < numsSize-1; i++){
//         min = nums[i];
//         for(j = i+1; j < numsSize; j++)
//             if(nums[j] < min){
//                 min = nums[j];
//                 min_id = j;
//             }
//         temp = nums[i];
//         nums[i] = nums[min_id];
//         nums[min_id] = temp;
//         min_id = i+1;
//     }

//     for(i = 0; i < numsSize; i++)
//         printf("%d ", nums[i]);

//     for(i = 0; i < numsSize; i++){
//         if(nums[i] != i)
//         return i;
//     }

//     return numsSize;
// }