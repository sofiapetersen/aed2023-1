#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *shortestCompletingWord( char *licensePlate, char **words, int wordsSize );

int main(){

    char licensePlate[] = "1s3 PSt", *words[4] = {"step", "steps", "stripe", "stepple"}, *finalWord;

    int size = 4;

    *finalWord = shortestCompletingWord( licensePlate, words, size );
    printf( "The shortest is: %s", finalWord );

    return 0;
}

char *shortestCompletingWord( char *licensePlate, char **words, int wordsSize ){
    int countLicensePlate[15] = {0}, countWord[20] = {0};        //pra contar os aparecer de cada caracter em licenseplate e em cada word
    int j, i, k, valid = 1;
    char *shortWord = NULL;

    //pesquisei pra ver no license se eh numero ou caracter, e como transformar tudo em minuscula


    for(i=0; i < (int)strlen(licensePlate); i++){
        if ( isalpha( licensePlate[i] ) ){      //se for letra
            countLicensePlate[ tolower( licensePlate[i] ) - 'a' ]++;    //transformar em minuscula

        }


          for(j=0; j < wordsSize; j++){
            for( i=0; i < ( int )strlen(words[j]); i++ ){
                countWord[tolower( words[j][i] ) - 'a'];    //transformando todas as letras das words em minusculas

            }
            for( k=0; k < 15; k++ ){        // percorre as duas arrays
                if( countLicensePlate[k] > countWord[j] ){
                    valid = 0;
                    break;
                }
            }
                // ai fez aqui ver se a palavra tem todos os caracteres que license tá pedindo

        if( valid && ( shortWord == NULL || strlen( words[j] < shortWord[j] ) ) ){
            shortWord = words[j];
        }
            // entao se a word que ta vendo tiver os caracteres e for a mais curta, shortWord vai receber essa word e vai ser retornada
    
        }
}
return shortWord;
}