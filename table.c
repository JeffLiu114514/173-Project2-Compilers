
#include "table.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

TABLE newTable() {
    TABLE table = (TABLE) malloc(sizeof(table));
    strcpy(table->alphabet, "|&~()01\0");

    table->blocks = (int **) malloc(8 * sizeof(int *));
    for (int i = 0; i < 8; i++) {
        table->blocks[i] = (int *) malloc(7 * sizeof(int));
    }
    //initialization with -1
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            table->blocks[i][j] = -1;
        }
    }


    return table;
}

TREE parse(char *input, TABLE table) {

}

void buildStack(int step, STACK stack, char input, TREE tree) {

}

int findIndex(TABLE parse_table, char character, int currentValue) {
    int position = 0; //TODO
    for (int i = 0; i < sizeof((*parse_table).alphabet); i++) {
        if (character == (*parse_table).alphabet[i]) {
            position = i;
            break;
        }
    }
    return (*parse_table).blocks[currentValue][position];
}
