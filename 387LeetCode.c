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
    int i, j, size;
    size = strlen(s);
    int temp[size] = {0};

    for(i=0; s[i] != '\0'; i++){
        temp[i]=1;
        for(j=i; s[j] != '\0'; j++){
            if(/*j != i &&*/ s[i] == s[j+1]){ 
                temp[i]++;
            }

        }
    }

    for(i=0; s[i] != '\0'; i++){
        if(temp[i] == 1){
            return i;
        }
    
    }
    return -1;

}