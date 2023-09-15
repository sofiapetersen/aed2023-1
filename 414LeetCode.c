#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void quickSort ( int data[], int left, int right );
int thirdMax(int* nums, int numsSize);

int main() {

    int nums[] = {4,2,2,3,1};
    int size = sizeof(nums) / sizeof(nums[0]);
    quickSort(nums, 0, size);
    
    int number = thirdMax(nums, size);

    printf("Third maximum: %d", number);

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

int thirdMax(int* nums, int numsSize){

    // int min, temp, i, j, min_id;

    // for(i = 0; i < numsSize-1; i++){
    //     min = nums[i];
    //     for(j = i+1; j < numsSize; j++)
    //         if(nums[j] < min){
    //             min = nums[j];
    //             min_id = j;
    //         }
    //     temp = nums[i];
    //     nums[i] = nums[min_id];
    //     nums[min_id] = temp;
    //     min_id = i+1;
    // }

    int i;
    if(numsSize == 2 || numsSize == 1){
        return nums[numsSize-1];
    } else if(numsSize >= 3){
        i = numsSize-3;        
    }

    if(nums[i] != nums[i-1] && nums[i] != nums[i+1]){
        return nums[i];
    } else{
        return nums[i-1];
    }
}