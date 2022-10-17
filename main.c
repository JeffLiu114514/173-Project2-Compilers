#include <stdio.h>
#include <string.h>

void Recursive_Descent_parser(){
    printf("Part one: Recursive Descent parser\nPlease enter input(type quit to quit)\n");
    char input[128];
    scanf("%s", input);
    while (strncmp(input, "quit", 4) != 0) {

    }
}

void Table_Driven_parser(){}

int main(){
    Recursive_Descent_parser();
    Table_Driven_parser();
}
