#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// sor, eu nao me orgulho dessa quantidade ifs, vou tentar diminuir em casa

int fillCups(int* amount, int amountSize);

int main(){

    int amount[3] = {0}, size = 3, answer;
    printf("type 0: ");
    scanf("%d", &amount[0]);
    printf("type 1: ");
    scanf("%d", &amount[1]);
    printf("type 2: ");
    scanf("%d", &amount[2]);

    answer = fillCups(amount, size);

    printf("\nAnswer %d", answer);

    return 0;

}

int fillCups(int* amount, int amountSize){

    int sec;

    if(amount[0] + amount[1] + amount[2] == 0){
        printf("Theres no cups to fill");
        return 0;
    }
    else if(amount[0] > (amount[1] + amount[2])){   // se o primeiro for o maior que a soma dos dois outros,
                                                // entao significa q vai parar os outros no meio e o primeiro
        sec = amount[0];                       // vai continuar 1 por segundo dai, entao meio q fica 1 por 1
        return sec;
    }
    else if(amount[0] == 0){
        if(amount[1] == amount[2] || amount[1] > amount[2]){
            sec = amount[1];        //nesse daqui se o primeiro for zero e os outros dois iguais ent eh o tempo deles
            return sec;
        }
        else{
        sec = (amount[1] + amount[2] + 2) / 2;      //se o primeiro for 0, entao ele nao precisa participar do calculo 
        return sec;                                 //dai se somar cada amount e dividir por 2 vai dar o tempo que precisa           
        }
    } 
    else if(amount[1] == 0){
        if(amount[0] == amount[2] || amount[0] > amount[2]){
            sec = amount[0];        //nesse daqui se o segundo for zero e os outros dois iguais ent eh o tempo deles
            return sec;
        }
        else{
        sec = (amount[0] + amount[2] + 2) / 2;      //se o segundo for 0, entao ele nao precisa participar do calculo 
        return sec;                                 //dai se somar cada amount e dividir por 2 vai dar o tempo que precisa           
        }
    }else if(amount[2] == 0){
        if(amount[0] == amount[1] || amount[0] > amount[1]){
            sec = amount[0];        //nesse daqui se o ultimo for zero e os outros dois iguais ent eh o tempo deles
            return sec;
        }
        else{
        sec = (amount[0] + amount[1] + 2) / 2;      //se o ultimo for 0, entao ele nao precisa participar do calculo 
        return sec;                                 //dai se somar cada amount e dividir por 2 vai dar o tempo que precisa           
        }
    }
    else{
         sec = amount[0] + (amount[1] + amount[2] - amount[0] + 1) / 2;      // else, nesse caso aqui ele vai dar o tempo somando e dividindo por 2 pq so pode 2 diferentes por vez ou um do mesmo
    }

    for(int i=0; i < amountSize; i++){
        printf("\nAmount[%d]: %d", i, amount[i]);
    }
    return sec;

}