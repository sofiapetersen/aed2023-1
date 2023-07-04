#include <stdio.h>
#include <stdlib.h>

int minCostClimbingStairs(int* cost, int costSize);


int main(){
    int size, total;
    printf("Size: ");
    scanf("%d", &size);
    int *cost = (int*)malloc(size*(sizeof(int)));
    cost[0] = 1;
    cost[1] = 100;
    cost[2] = 1;
    cost[3] = 1;
    cost[4] = 1;
    cost[5] = 100;
    cost[6] = 1;
    cost[7] = 1;
    cost[8] = 100;
    cost[9] = 1;
    total = minCostClimbingStairs(cost, size);
    printf("%d", total);
return 0;
}



int minCostClimbingStairs(int* cost, int costSize){
   int start, next=0, doubleNext=0, total=0;
   printf("Start 0 or 1: ");
   scanf("%d", &start);
   if (start == 0){
       total += cost[0];
do{

       next++; // next anda um
       doubleNext += 2; //doubleNext anda 2

       if (cost[next] < cost[doubleNext] && next <= costSize){
           total += cost[next];
           next++;
           doubleNext++;
       }
       else{
           total += cost [doubleNext];
           next++;
           doubleNext++;
       }

   }while (doubleNext <= costSize);
   }

   else{
       total += cost[1];
       next=1;
       doubleNext=1;
       do{
           next++;
           doubleNext += 2;
           if(cost[next] < cost[doubleNext] && next <= costSize){
               total += cost[next];
               next++;
               doubleNext++;
           }
           else{
               total += cost[doubleNext];
               next++;
               doubleNext++;
           }
       }while (doubleNext <= costSize);
   }
   return total;
}