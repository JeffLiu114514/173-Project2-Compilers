#include <stdio.h>
#include <string.h>
#include "Recursive.h"
#include "table.h"

void Recursive_Descent_parser(){
    printf("Part one: Recursive Descent parser\nPlease enter input(type quit to quit)\n");
    char input[128];
    scanf("%s", input);

    while (strncmp(input, "quit", 4) != 0) {
        nextTerminal = input;
        TREE parseTree = parseStart();
        if (parseTree != NULL) {
            printf("Valid input. The tree is: \n");
            printTree(parseTree, 0);
            printf("Please enter input(type quit to quit)\n");
            scanf("%s", input);
        } else {
            printf("Invalid input. \n");
            printf("Please enter input(type quit to quit)\n");
            scanf("%s", input);
        }
    }
}

void Table_Driven_parser(){
    printf("Part two: Table-driven parser\nPlease enter input(type quit to quit)\n");
    char input[128];
    scanf("%s", input);
    while (strncmp(input, "quit", 4) != 0) {
        nextTerminal = input;
        TABLE table = newTable();
        TREE parseTree = parse(input, table);
        if (parseTree != NULL) {
            printf("Valid input. The tree is: \n");
            printTree(parseTree, 0);
            printf("Please enter input(type quit to quit)\n");
            scanf("%s", input);
        } else {
            printf("Invalid input. \n");
            printf("Please enter input(type quit to quit)\n");
            scanf("%s", input);
        }
    }
}

int main(){
    Recursive_Descent_parser();
    Table_Driven_parser();
}
