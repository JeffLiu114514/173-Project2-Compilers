//
// Created by 23566 on 2022/10/17.
//

#ifndef INC_173PROJ2_TABLE_H
#define INC_173PROJ2_TABLE_H

#include "Recursive.h"
#include "stack.h"
typedef struct table* TABLE;

struct table {
    char alphabet[7];
    int** blocks;
};

extern TABLE newTable();
extern TREE parse(char* input, TABLE table);
extern void buildStack(int step, STACK stack, char input, TREE tree);
extern int findIndex(TABLE parse_table, char character, int currentValue);
#endif //INC_173PROJ2_TABLE_H
