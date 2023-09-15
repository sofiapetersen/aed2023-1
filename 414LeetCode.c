#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


int thirdMax(int* nums, int numsSize);

int main() {

    int nums[] = {4,2,1};    
    int size = sizeof(nums) / sizeof(nums[0]);
    
    int number = thirdMax(nums, size);

    printf("Third maximum: %d", number);

    return 0;
}


// int thirdMax(int* nums, int numsSize){   //por sort ta dando algum erro de ler variavel nao incializada

//     int min, temp, i, j, min_id = 0;

//     for(i = 0; i < numsSize; i++){
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

//     //int i;
//     if(numsSize == 2 || numsSize == 1){
//         return nums[numsSize-1];
//     } else if(numsSize >= 3){
//         i = numsSize-3;        
//     }

//     if(nums[i] != nums[i-1] && nums[i] != nums[i+1]){
//         return nums[i];
//     } else{
//         return nums[i-1];
//     }
// }

int thirdMax(int* nums, int numsSize){
    long max = LONG_MIN, secondMax = LONG_MIN, thirdMax = LONG_MIN; //numeros pequenos
    int i;
    for(i = 0; i < numsSize; i++){
        if(nums[i] > max){  //se for maior que maior, ele vira o maior
            thirdMax = secondMax;
            secondMax = max;
            max = nums[i];
        } else if(nums[i] < max && nums[i] > secondMax){    //se tiver entre o maior e o segundo maior, ele vira o segundo maior
            thirdMax = secondMax;
            secondMax = nums[i];
        } else if(nums[i] < secondMax && nums[i] > thirdMax){   //se tiver entre o segundo maior e o terceiro maior, ele vira o terceiro maior
            thirdMax = nums[i];
        }
    }

    if (thirdMax != LONG_MIN){    //se o terceiro nao se manteve -1 pq nao tinha tres numeros
        return thirdMax;
    } else if (secondMax != LONG_MIN){    //se tinha dois numeros entao retorna o maior deles
        return max;
    } else{     //se so tinha um numero retorna ele mesmo
        return max;
    }
}