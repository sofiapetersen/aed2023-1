#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX = 10

struct theStudent{
    int ra;
    char name[100];
};

typedef struct theStudent student_t;

struct theStack{
    student_t students[MAX];
    int top;
    int base;
    int limit;
};
typedef struct theStack stack_t;

void Reset ( stack_t *stack );
bool Clear ( stack_t *stack );
bool Push ( stack_t *stack, student_t *item );
void Pop ( stack_t *stack, student_t *student );


int main(){

    return 0;
}

void Reset ( stack_t *stack ){
    stack->top = 0;
    stack->base = 0;
    stack->limit = 0;
}

bool Clear ( stack_t *stack ){
    return stack->top == 0;
}

bool Push ( stack_t *stack, student_t *item ){
    if( !Full ( stack ) ){
        stack->students[stack->top] = *item;
        stack->top++;
        return true;
    }
    else{
        return false;
    }
}

void Pop ( stack_t *stack, student_t *student ){
    if( stack->top == 0 ){
        return;
    }
    stack->top--;
    *student = stack->students[stack->top];

}


