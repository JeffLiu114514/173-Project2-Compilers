//
// Created by 23566 on 2022/10/17.
//

#ifndef INC_173PROJ2_STACK_H
#define INC_173PROJ2_STACK_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Recursive.h"
typedef struct stack* STACK;
struct stack {
    TREE* content;
    int top;
    unsigned size;
};

extern STACK constructStack(unsigned size);
extern bool isEmpty(STACK stack);
extern TREE pop(STACK stack);
extern void push(STACK stack, TREE node);


#endif //INC_173PROJ2_STACK_H
