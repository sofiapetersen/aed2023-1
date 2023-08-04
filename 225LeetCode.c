#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int* data;
    int top;
    int capacity;

} MyStack;


MyStack* myStackCreate() {
    MyStack *stack = (MyStack *)malloc(sizeof(MyStack));
    stack->data = (int*)malloc(sizeof(int)*100);
    stack->top = -1;
    stack->capacity = 100;
    return stack;
}

void myStackPush(MyStack* obj, int x) {
if (obj->top == obj->capacity -1){
    
    return;
}
obj->top++;
obj->data[obj->top] = x;
  
}

int myStackPop(MyStack* obj) {
  if(obj->top == -1){
      return -1;
  }
  int value = obj->data[obj->top];
  obj->top--;
  return value;
}

int myStackTop(MyStack* obj) {
  if(obj->top == -1){
      return -1;
  }
return obj->data[obj->top];
}

bool myStackEmpty(MyStack* obj) {
  return obj->top == -1;
}

void myStackFree(MyStack* obj) {
    free(obj->data);
    free(obj);
}

void myStackPrint(MyStack *obj){
    printf("\nStack Elements:\n");
    for(int i = obj->top; i >= 0; i--){
        printf("%d\n", obj->data[i]);
    }
    printf("\n");
}

int main(){

  MyStack* obj = myStackCreate();
  int x, menu;

do{ 
  printf("\nMENU\n1. Push\n2. Pop\n3. Show Top\n4. Is it Empty?\n5. Print Stack\n6. Exit\nChoose: ");
  scanf("%d", &menu);

  switch(menu){
    case 1:
    printf("Value to push: ");
    scanf("%d", &x);
    myStackPush(obj, x);
    break;

    case 2:
    printf("Popped value: %d", myStackPop(obj));
    break;

    case 3:
    printf("Top value: %d", myStackTop(obj));
    break;

    case 4:
    printf("%s", myStackEmpty(obj) ? "Yes" : "No");
    break;

    case 5:
    myStackPrint(obj);
    break;

    case 6:
    myStackFree(obj);
    break;

  }
} while(menu != 6);

 return 0;
}