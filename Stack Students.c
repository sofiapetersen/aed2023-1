#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10

struct theStudent{
    int age;
    char name[100];
};

typedef struct theStudent student_t;

struct theStack{
    student_t *students[MAX];
    int top;
    int base;
    int limit;
};
typedef struct theStack stack_t;

void Reset ( stack_t *stack );
bool Clear ( stack_t *stack );
bool Push ( stack_t *stack, student_t *item );
void Pop ( stack_t *stack, student_t **student );
void ShowStack ( stack_t *stack );
void PopByName ( stack_t *stack, const char *name );


int main(){

    int menu, age;
    char name[100], nameRemove[100];
    stack_t stack;
    Reset(&stack);       //inicializar a pilha

    do{
    printf( "\n----MENU----\n1-Add Student\n2-Remove from Top\n3-Remove Name\n4-Show Students\n5-Clear Stack\n6-Leave\nChoose option: " );
    scanf( "%d", &menu );
    getchar();

    switch(menu){
        case 1:
       printf( "\n----REGISTER----\nName: " );
        gets(name);
        printf( "Age: " );
        scanf( "%d", &age );
        getchar();

        student_t *newStudent = ( student_t* )malloc( sizeof ( student_t ) );
        newStudent->age = age;
        strcpy( newStudent->name, name );
        Push( &stack, newStudent );
        break;

        case 2:
        printf("\n----REMOVE----\n");
        if(stack.top > 0){
            student_t *topStudent;      
            Pop( &stack, &topStudent );
            free(topStudent);
            printf("\nTop student deleted!\n");
        }else{
            printf("\nStack is already empty!\n");
        }
        break;

        case 3:
        printf( "----REMOVE BY NAME----\nStudent: " );
        gets( nameRemove );
        nameRemove[ strcspn( nameRemove, "\n" ) ] = '\0';
        PopByName( &stack, nameRemove);
        printf( "\nStudent %s was removed!\n", nameRemove);
        break;
    
        case 4:
        ShowStack(&stack);
        break;

        case 5:
        if( stack.top != 0 ){
        while ( !Clear(&stack) ){
        student_t *tempStudent;
        Pop( &stack, &tempStudent );
        free( tempStudent );
        }
        printf( "\nThe stack is empty now!\n" );
        } else{
            printf( "\nThe stack is already empty\n" );
        }
        break;

        case 6:
        while ( !Clear(&stack) ){
        student_t *tempStudent;
        Pop( &stack, &tempStudent );
        free( tempStudent );
        }
        printf( "Exiting Stack..." );
        break;
    }

}while( menu != 6 );
    return 0;
}

void Reset ( stack_t *stack ){
    for( int i=0; i<MAX; i++ ){
        stack->students[i] = NULL;
    } 
    stack->top = 0;
    stack->base = 0;
    stack->limit = MAX;
}

bool Clear ( stack_t *stack ){
    return stack->top == 0;
}

bool Full ( stack_t *stack ){
    return stack->top == MAX;
}

bool Push ( stack_t *stack, student_t *item ){
    if( !Full ( stack ) ){      //desde que a pilha nao esteja cheia
        stack->students[stack->top] = item;    //students vai receber a info
        stack->top++;           //o topo vai incrementar
        return true;
    }
    else{
        return false;
    }
}

void Pop ( stack_t *stack, student_t **student ){
    if( stack->top == 0 ){      //se o topo for 0 nao tem oq tirar
        *student = NULL; // pilha vazia
        return;
    }
    stack->top--;   //se nao for zero, tira 1 do topo
    *student = stack->students[stack->top]; //ele salva a informação que tava no topo, mas ela nao ta mais no topo

}

void ShowStack ( stack_t *stack ){
    stack_t tempStack;
    Reset ( &tempStack );

    if(stack->top == 0){
        printf("\nThe Stack is Empty\n");
    }
int i=0;
    while( !Clear( stack ) ){
        student_t *tempStudent;
        Pop ( stack, &tempStudent );
        Push ( &tempStack , tempStudent);
        printf( "\n----STUDENT %d----\nName: %s\nAge: %d\n", i, tempStudent->name, tempStudent->age );
         i++;
        
    }

    // int i=tempStack.top-1;

    while ( !Clear( &tempStack ) )
    {
        student_t *tempStudent;
        Pop ( &tempStack, &tempStudent );   // desempilha da temporaria       
       // printf( "\n----STUDENT %d----\nName: %s\nAge: %d\n", i, tempStudent->name, tempStudent->age );
        Push ( stack, tempStudent );        //coloca na original
       // i--;
    }
    
}

void PopByName ( stack_t *stack, const char *name ){
    stack_t tempStack;
    Reset( &tempStack ); //pra poder inicializar essa pilha temporaria

    while ( !Clear( stack ) ){       //pra percorrer a pilha enqt procura o nome
        student_t *tempStudent;
        Pop( stack, &tempStudent );     // tira da pilha original
        if( strcmp( tempStudent->name, name ) != 0 ){   //compara o nome da pilha com o nome que quero remover
            Push( &tempStack, tempStudent ); //coloca na pilha temporaria pq nao eh o nome que quero remover ainda
          // printf( "\nTEMP:\n" ); //so pra ver qq ta acontecendo
          // ShowStack( &tempStack );
        } else{
            free( tempStudent );  //significa que achou e ta liberando
            break;      //quebra o looping pq ja achei e deletei oq eu queria
        }
    }
    
    while( !Clear( &tempStack ) ){        //até a pilha temporaria ficar vazia
        student_t *tempStudent;     //cria de novo pra poder trocar de uma pilha pra outra
        Pop( &tempStack, &tempStudent );    //tira da pilha temporaria
        Push( stack, tempStudent );     // coloca na pilha original
        //printf( "\nORIG:\n" );  //so pra ver qq ta acontecendo
        //ShowStack( stack );
    }

}