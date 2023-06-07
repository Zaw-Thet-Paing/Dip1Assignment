#include "stdio.h"
#include "stdlib.h"
#define MAX_OF_STACK 10

int count = 0;

struct stack{
    int data[MAX_OF_STACK];
    int top;
};

typedef struct stack st;

void createEmptyStack(st* myStack){
    myStack->top = -1;
}

int isStackFull(st *myStack){
    if(myStack->top == (MAX_OF_STACK - 1)){
        return 1;
    }else{
        return 0;
    }
}

int isStackEmpty(st *myStack){
    if(myStack->top == -1){
        return 1;
    }else{
        return 0;
    }
}

void push(st *myStack, int value){
    if(isStackFull(myStack)){
        printf("Stack is full!\n");
    }else{
        myStack->top++;
        myStack->data[myStack->top] = value;
    }
    count++;
}

void pop(st *myStack){
    if(isStackEmpty(myStack)){
        printf("Stack is empty");
    }else{
        printf("Pop from stack is %d\n", myStack->data[myStack->top]);
        myStack->top--;
    }
    count--;
}

int main(){

    st* myStack = (st *)malloc(sizeof(st));

    createEmptyStack(myStack);

    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    push(myStack, 40);
    push(myStack, 100);

    int index = 0;
    while(count != 0){
        printf("Value is %d\n", myStack->data[index]);
        index++;
        count--;
    }

    printf("\n");

    pop(myStack);
    pop(myStack);
    pop(myStack);
    pop(myStack);
    pop(myStack);

    return 0;
}