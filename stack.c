//
// Created by 23566 on 2022/10/17.
//
#include "stack.h"

STACK newStack(unsigned size){
    STACK stack = (STACK)malloc(sizeof(STACK));
    stack->content = (TREE*)malloc(stack->size * sizeof(TREE));
    stack->top = -1;
    stack->size = size;
    return stack;
}

bool isEmpty(STACK stack){
    return stack->top == -1;
}

TREE pop(STACK stack){
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->content[stack->top--];
}

void push(STACK stack, TREE node){
    stack->content[++stack->top] = node;
}