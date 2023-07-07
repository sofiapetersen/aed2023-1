#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *shortestCompletingWord( char *licensePlate, char **words, int wordsSize );

int main(){

    char licensePlate[] = "1s3 PSt", *words[4], finalWord[10];
    words[0] = "step";
    words[1] = "steps";
    words[2] = "stripe";
    words[3] = "stepple";

    int size = 8;

    finalWord[10] = shortestCompletingWord( licensePlate, words, size );
    printf( "The shortest is: %s", finalWord );

    return 0;
}

char *shortestCompletingWord( char *licensePlate, char **words, int wordsSize ){

    int j, i;
    char final[15];

    for(i=0; i < (int)strlen(licensePlate); i++){
        for(j=0; j < wordsSize; j++){
            if (words[j] == licensePlate[i]){
                final[i] = words[j];
            }else if(words[j] == licensePlate[i]){
                final[i] = words[j];
            }else if(words[j] == licensePlate[i]){
                final[i] = words[j];
            }else if(words[j] == licensePlate[i]){
                final[i] = words[j];
                }
    
        }
}
return final;
}