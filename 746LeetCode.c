/*You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.

You can either start from the step with index 0, or the step with index 1.

Return the minimum cost to reach the top of the floor.

 

Example 1:

Input: cost = [1,100,1,1,1,100,1,1,100,1]
Output: 6
Explanation: You will start at index 0.
- Pay 1 and climb two steps to reach index 2.
- Pay 1 and climb two steps to reach index 4.
- Pay 1 and climb two steps to reach index 6.
- Pay 1 and climb one step to reach index 7.
- Pay 1 and climb two steps to reach index 9.
- Pay 1 and climb one step to reach the top.
The total cost is 6.*/


#include <stdio.h>
#include <stdlib.h>

int MinCostClimbingStairs( int* cost, int costSize );
int MinCost( int a, int b );


int main(){
    int size=10, total;
    int *cost = ( int* )malloc( size * ( sizeof ( int )));
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
    total = minCostClimbingStairs( cost, size );
    printf( "%d", total );

    free( cost );

return 0;
}



int MinCostClimbingStairs( int* cost, int costSize ){
    int i, result=0;
    int *dp = ( int* )malloc(( costSize + 1 ) * sizeof( int ));  //criacao de um dinamico e cada dp[i] tem o custo minimo pra chegar na posicao i da escada
    dp[0] = 0;
    dp[1] = 0;
    //tanto o 0 e o 1 nao tem custo pq n precisa gastar pra comecar

    for( i=2; i <= costSize; i++ ){        // percorrendo o vetor | i começa em 2 pq ele compara os dois anteriores
        dp[i] = MinCost( dp[i-1] + cost[i-1], dp[i-2] + cost[i-2] ); //pegando os dois valores e passando pra comparação
            // como pode subir 1 ou 2 degraus, ele compara qual tem custo mais baixo, entre o custo de subir e o custo da posicao
            // ai vai somando e quando chegar no ultimo vetor, que no caso eh o costSize vai ter a soma dos custos
    }

    result = dp[costSize];
    free( dp );
    return result;
}

int MinCost( int a, int b ){
    return a < b ? a : b;       // versao reduzida de if (a<b) return a; else return b;
}