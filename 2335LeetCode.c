#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fillCups(int* amount, int amountSize);

int main(){

    int *amount[3] = {0}, size = 3, answer;
    printf("type 0: ");
    scanf("%d", &amount[0]);
    printf("type 1: ");
    scanf("%d", &amount[1]);
    printf("type 3: ");
    scanf("%d", &amount[2]);

    printf("\nAmount[0]: %d\nAmount[1]: %d\nAmount[2]: %d\nsize: %d\n", amount[0], amount[1], amount[2], size);

    answer = fillCups(amount, size);

    printf("Answer %d", answer);

    return 0;

}

/*int fillCups(int* amount, int amountSize){
    int sec;
    int i;
    
    for(i=0; i < amountSize; i++){
    sec += amount[i];
}

    sec = sec/2;
    sec = sec+2;
    return sec;
}
*/

int fillCups(int* amount, int amountSize){

    int sec;

    if(amount[0] >= (amount[1] + amount[2])){
        return amount[0];
    }
    else{
        sec = amount[0] + (amount[1] + amount[2] - amount[0] + 1) / 2;
    } 
    return sec;

}