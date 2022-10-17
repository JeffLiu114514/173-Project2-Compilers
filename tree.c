//
// Created by 23566 on 2022/10/17.
//
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "tree.h"

#define FAILED NULL

/**
 * Returns true if the current input symbol is the given char, otherwise false.
 */
bool lookahead(char c) {
    return *nextTerminal == c;
}

/**
 * If the current input symbol is the given char, advance to the next
 * character of the input and return true, otherwise leave it and return false.
 */
bool match(char c) {
    if (lookahead(c)) {
        nextTerminal += 1;
        return true;
    } else {
        return false;
    }
}

void free_tree(TREE root){
    if(root->leftmostChild != NULL){
        free_tree(root->leftmostChild);
    }
    if(root->rightSibling != NULL){
        free_tree(root->rightSibling);
    }
    free(root);
}

TREE parseStart() {
    TREE parseTree = E();
    if(lookahead('\0')){
        return parseTree;
    }
    else{
        free_tree(parseTree);
        return NULL;
    }
}

void printTree(TREE tree, int depth){
    if(tree==NULL){
        return;
    }
    else{
        for(int i = 0; i < depth; i++){
            printf("  ");
        }
        printf("%c\n", tree->label);
        printTree(tree->leftmostChild,depth+1);
        printTree(tree->rightSibling, depth);
    }
}

//int main() {
//    parseTree = parse("()()"); /* in practice, a string of terminals would be read from input */
//    printf("%p\n", parseTree); /* you need to pretty-print the parse tree */
//}

TREE makeNode0(char x) {
    TREE root;
    root = (TREE) malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode1(char x, TREE t) {
    TREE root;
    root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}

TREE makeNode2(char x, TREE t1, TREE t2) {
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    return root;
}

TREE makeNode3(char x, TREE t1, TREE t2, TREE t3) {
    TREE root;
    root = makeNode2(x, t1, t2);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    return root;
}

TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4) {
    TREE root;
    root = makeNode3(x, t1, t2, t3);
    t3->rightSibling = t4;
    return root;
}

TREE E(){

}
TREE ET() {

}
TREE T(){

}
TREE TT(){

}
TREE F(){

}
TREE S(){

}
TREE ST(){

}
TREE B(){

}
