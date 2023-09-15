#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isAnagram(char *s, char *t);

int main() {
    char s[100], t[100];

    printf("Type a word: ");
    scanf("%s", s);

    printf("Type another word: ");
    scanf("%s", t);

    if (isAnagram(s, t)) {
        printf("They are anagrams\n");
    } else {
        printf("They are not anagrams\n");
    }

    return 0;
}


bool isAnagram(char *s, char *t) {

    if (strlen(s) != strlen(t)) //primeiro ja olha se tem mesmo tamanho, pq se nao tiver nem adianta, ja eh falso
        return false;  
    
    int count[256] = {0}; //um vetor de contagem que conta tudo do ascii

    for (int i = 0; s[i] != '\0'; i++) {
        count[(int)s[i]]++; // preenche esse vetor com as ocorrências das letras em s
    }

    /*  exemplo:
    count[97] = 1  -> 'a'   os indices sao da tabela ascii
    count[109] = 1 -> 'm'
    count[111] = 1 -> 'o'
    count[114] = 1 -> 'r'
    */

    for (int i = 0; t[i] != '\0'; i++) {
        count[(int)t[i]]--; // decrementa esse vetor com as ocorrências das letras em t
    }

    /*  exemplo:
    count[114] = 0 -> 'r'   //se for o mesmo indice, entao ele vai decrementar no lugar certo e 
    count[111] = 0 -> 'o'     ficar 0, se ficar -1 ou algo diferente disso é pq nao eh anagrama
    count[109] = 0 -> 'm'
    count[97] = 0  -> 'a'
    */

    // ve se todas as contagens dao zero, dai se for 0 entao eh anagrama
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            return false;
        }
    }

    return true;
}