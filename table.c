#include "Recursive.h"
#include "table.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define FAILED NULL

TABLE newTable() {
    TABLE table = (TABLE) malloc(sizeof(table));
    strcpy(table->alphabet, "|&~(01)");

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
// Epsilon productions are counted as unique productions
//    Table is like:
//        |   &   ~   (   0   1   )
//    E           0   0   0   0
//    ET  1   2   2   2   2   2   2
//    T           3   3   3   3
//    TT  5   4   5   5   5   5   5
//    F           6   7   8   8
//    S                   9   9
//    ST  10  10  10  10  11  11  10
//    B                   12  12
// Empty field is -1
    for (int i = 2; i < 6; ++i) {
        table->blocks[0][i] = 0;
        table->blocks[2][i] = 3;
    }
    table->blocks[1][0] = 1;
    for (int i = 1; i < 7; ++i) {
        table->blocks[1][i] = 2;
    }
    for (int i = 0; i < 7; ++i) {
        table->blocks[3][i] = 5;
    }
    table->blocks[3][1] = 4;
    table->blocks[4][2] = 6;
    table->blocks[4][3] = 7;
    for (int i = 0; i < 7; ++i) {
        table->blocks[6][i] = 10;
    }
    for (int i = 4; i < 6; ++i) {
        table->blocks[4][i] = 8;
        table->blocks[5][i] = 9;
        table->blocks[6][i] = 11;
        table->blocks[7][i] = 12;
    }

    return table;
}

char isTerminal(TREE node) {
    char* c = node->label;
    if (strcmp(c, "|") == 0) {
        return '|';
    } else if (strcmp(c, "&") == 0){
        return '&';
    } else if (strcmp(c, "~") == 0){
        return '~';
    }else if (strcmp(c, "(") == 0){
        return '(';
    }else if (strcmp(c, ")") == 0){
        return ')';
    }else if (strcmp(c, "0") == 0){
        return '0';
    }else if (strcmp(c, "1") == 0){
        return '1';
    }else if (strcmp(c, "e") == 0) {
        return 'e';
    }
    return 0;
}

int findRow(TREE node) {
    char* c = node->label;
    if (strcmp(c, "E") == 0) {
        return 0;
    } else if (strcmp(c, "ET") == 0){
        return 1;
    } else if (strcmp(c, "T") == 0){
        return 2;
    }else if (strcmp(c, "TT") == 0){
        return 3;
    }else if (strcmp(c, "F") == 0){
        return 4;
    }else if (strcmp(c, "S") == 0){
        return 5;
    }else if (strcmp(c, "ST") == 0){
        return 6;
    }else if (strcmp(c, "B") == 0){
        return 7;
    }
    return -1;
}

int findIndex(TABLE table, char c, int row) {
    int column = 0;
    for (int i = 0; i < sizeof((*table).alphabet); i++) {
        if (c == (*table).alphabet[i]) {
            column = i;
            break;
        }
    }
    return (*table).blocks[row][column];
}

TREE parse(char *input, TABLE table) {
    STACK stack = constructStack(strlen(input) * 10);
    TREE temp;
    int rowNum;
    char currentChar;

//    push start symbol
//    while stack not empty {
//            Y = pop stack
//            if Y is a terminal {
//                match and consume it, else fail
//            } else {
//                // Y is a non-terminal
//                select production for Y using lookahead
//                push RHS of production onto stack
//            }
//    }
    TREE first = makeNode0("E");
    push(stack, first);
    while (!isEmpty(stack)) {
        temp = pop(stack);
//        printf("%s\n", temp->label);
        if (isTerminal(temp)) {
//            printf("%s is terminal\n", temp->label);
            if (isTerminal(temp) == 'e') continue;
            if (!match(isTerminal(temp))) {
//                printf("terminal not matched\n");
                return FAILED;
            }
        }
        else {
            currentChar = *nextTerminal;
            rowNum = findRow(temp);
            if (rowNum == -1) {
//                printf("row col failed\n");
                return FAILED;
            }
            else {
                if (lookahead('\0')) { //special case: when string reaches end but stack is not empty
//                    printf("Input end detected. Inserted eps\n");
                    TREE eps = makeNode0("e");
                    temp->leftmostChild = eps;
                    push(stack, eps);
                }
                else {
                    int nextProduction = findIndex(table, currentChar, rowNum);
//                    printf("Current char is %c \n", currentChar);
//                    printf("%d\n", nextProduction);
                    buildStack(nextProduction, stack, currentChar, temp);
                }

            }
        }
    }
    if (lookahead('\0')) {
        return first;
    } else {
        return NULL;
    }
}

void buildStack(int production, STACK stack, char input, TREE tree) {
    if (production == 0) { //E -> T ET
        TREE t = makeNode0("T");
        TREE et = makeNode0("ET");
        tree->leftmostChild = t;
        t->rightSibling = et;
        push(stack, et);
        push(stack, t);
    } else if (production == 1) { //ET -> | E
        TREE or = makeNode0("|");
        TREE e = makeNode0("E");
        tree->leftmostChild = or;
        or->rightSibling = e;
        push(stack, e);
        push(stack, or);
    } else if (production == 2) { //ET -> epsilon
        TREE eps = makeNode0("e");
        tree->leftmostChild = eps;
        push(stack, eps);
    } else if (production == 3) { //T -> F TT
        TREE f = makeNode0("F");
        TREE tt = makeNode0("TT");
        tree->leftmostChild = f;
        f->rightSibling = tt;
        push(stack, tt);
        push(stack, f);
    } else if (production == 4) { //TT -> & T
        TREE and = makeNode0("&");
        TREE t = makeNode0("T");
        tree->leftmostChild = and;
        and->rightSibling = t;
        push(stack, t);
        push(stack, and);
    } else if (production == 5) { //TT -> epsilon
        TREE eps = makeNode0("e");
        tree->leftmostChild = eps;
        push(stack, eps);
    } else if (production == 6) { //F -> ~ F
        TREE negate = makeNode0("~");
        TREE f = makeNode0("F");
        tree->leftmostChild = negate;
        negate->rightSibling = f;
        push(stack, f);
        push(stack, negate);
    } else if (production == 7) { //F -> ( E )
        TREE leftP = makeNode0("(");
        TREE e = makeNode0("E");
        TREE rightP = makeNode0(")");
        tree->leftmostChild = leftP;
        leftP->rightSibling = e;
        e->rightSibling = rightP;
        push(stack, rightP);
        push(stack, e);
        push(stack, leftP);
    } else if (production == 8) { //F -> S
        TREE s = makeNode0("S");
        tree->leftmostChild = s;
        push(stack, s);
    } else if (production == 9) { //S -> B ST
        TREE b = makeNode0("B");
        TREE st = makeNode0("ST");
        tree->leftmostChild = b;
        b->rightSibling = st;
        push(stack, st);
        push(stack, b);
    } else if (production == 10) { //ST -> epsilon
        TREE eps = makeNode0("e");
        tree->leftmostChild = eps;
        push(stack, eps);
    } else if (production == 11) { //ST -> S
        TREE s = makeNode0("S");
        tree->leftmostChild = s;
        push(stack, s);
    } else if (production == 12) { //B -> 0 | 1
        if (input == '0') {
            TREE num = makeNode0("0");
            tree->leftmostChild = num;
            push(stack, num);
        } else if (input == '1') {
            TREE num = makeNode0("1");
            tree->leftmostChild = num;
            push(stack, num);
        }
    }

}


