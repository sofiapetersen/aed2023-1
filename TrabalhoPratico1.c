#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *shortestCompletingWord( char *licensePlate, char **words, int wordsSize );

int main(){

    char licensePlate[] = "1s3 PSt";
    char *words[4] = {"step", "steps", "stripe", "stepple"};
    int size = 4;

    char *finalWord = shortestCompletingWord( licensePlate, words, size );
    printf( "The shortest is: %s", finalWord );

    return 0;
}

char *shortestCompletingWord( char *licensePlate, char **words, int wordsSize ){
    int countLicensePlate[26] = {0};  // Array para contar as ocorrências de cada caractere em licensePlate
    char *shortWord = NULL;

    //pesquisei pra ver no license se eh numero ou caracter, e como transformar tudo em minuscula


    for (int i = 0; i < (int)strlen(licensePlate); i++) {
        if (isalpha(licensePlate[i])) {      //se for letra
            countLicensePlate[tolower(licensePlate[i]) - 'a']++;    //transformar em minuscula

        }
        
          for (int i = 0; i < wordsSize; i++) {
            int countWord[26] = {0};        //pra contar os aparecer de cada caracter em words
            for (int j = 0; j < (int)strlen(words[i]); j++) {
                 if (isalpha(words[i][j])) {
                countWord[tolower(words[i][j]) - 'a']++;    //transformando todas as letras das words em minusculas
                }
            }
            int valid = 1;
            for (int k = 0; k < 26; k++) {    // percorre as duas arrays
                if (countLicensePlate[k] > countWord[k]) {
                    valid = 0;
                    break;
                }
            }
                // ai fez aqui ver se a palavra tem todos os caracteres que license tá pedindo

        if (valid && (shortWord == NULL || strlen(words[i]) < strlen(shortWord))) {
            shortWord = words[i];
        }
            // entao se a word que ta vendo tiver os caracteres e for a mais curta, shortWord vai receber essa word e vai ser retornada
    
        }
}
    return shortWord;
}