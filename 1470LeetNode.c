/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shuffle(int* nums, int numsSize, int n, int* returnSize){
        int *new = (int*)malloc(sizeof(int)* numsSize);
        int i, j;
        for(i=0, j=0; i < n; i++, j += 2){
            new[j] = nums[i];
            new[j+1] = nums[i+n];
        }
        *returnSize = numsSize;

        return new;
    }
