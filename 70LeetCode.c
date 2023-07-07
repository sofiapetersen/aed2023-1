/*
Leet Code 70. Climbing Stairs
You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?*/

#include <stdio.h>
#include <stdlib.h>

int climbStairs( int n );

int main(){
    int steps, total;

    printf( "Type total steps: " );
    scanf( "%d", &steps );

   total = climbStairs( steps );
    printf( "Ways to climb: %d", total );

    return 0;
}

int climbStairs( int n ){

    int step = 0, nextStep = 1, total, i;
    if(n <= 3){
        return n;       //pq dai so vai ter jeito n de subir
    }

    for( i=n; i > 0; i-- ){
        total = step + nextStep;        // aqui no primeiro laço o total vai receber 0 + 1 do primeiro passo
        step = nextStep;                // dai mais o next recebe o nextStep pra poder somar de novo dps
        nextStep = total;               // e no nextStep acumula quantos jeitos ja tem
    }

    return total;
}