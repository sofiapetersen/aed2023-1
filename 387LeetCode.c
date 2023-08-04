#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int firstUniqChar(char * s);

int main(){
    char string[30];
    int answer;

    printf("type: ");
    scanf("%[^\n]s", string);
    printf("\ntyped: %s", string);

    answer = firstUniqChar(string);
    printf("\nanswer: %d\n", answer);
    return 0;



}

int firstUniqChar(char * s){
    int i, size;
    size = strlen(s);
    int temp[250] = {0};

    for(i=0; i < size; i++){
        temp[s[i]]++;   //aqui ele marca com 1 todas as letras pq elas vao aparecer pelo menos uma vez
    }

    for(i=0; i < size; i++){
        if(temp[s[i]] == 1){
            return i;
        }
    
    }
    return -1;

}