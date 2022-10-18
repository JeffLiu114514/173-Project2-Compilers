
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Recursive.h"

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

//void free_tree(TREE root){
//    if(root->leftmostChild != NULL){
//        free_tree(root->leftmostChild);
//    }
//    if(root->rightSibling != NULL){
//        free_tree(root->rightSibling);
//    }
//    free(root);
//}

TREE parseStart() {
    TREE parseTree = E();
    if (lookahead('\0')) {
        return parseTree;
    } else {
//        free_tree(parseTree);
        return NULL;
    }
}

void printTree(TREE tree, int depth) {
    if (tree == NULL) {
        return;
    } else {
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        printf("%s\n", tree->label);
        printTree(tree->leftmostChild, depth + 1);
        printTree(tree->rightSibling, depth);
    }
}

//int main() {
//    parseTree = parse("()()"); /* in practice, a string of terminals would be read from input */
//    printf("%p\n", parseTree); /* you need to pretty-print the parse tree */
//}

TREE makeNode0(char *x) {
    TREE root;
    root = (TREE) malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode1(char *x, TREE t) {
    TREE root;
    root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}

TREE makeNode2(char *x, TREE t1, TREE t2) {
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    return root;
}

TREE makeNode3(char *x, TREE t1, TREE t2, TREE t3) {
    TREE root;
    root = makeNode2(x, t1, t2);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    return root;
}

TREE makeNode4(char *x, TREE t1, TREE t2, TREE t3, TREE t4) {
    TREE root;
    root = makeNode3(x, t1, t2, t3);
    t3->rightSibling = t4;
    return root;
}

TREE B() {
    if (lookahead('0')) {//production1
        if (!match('0')) return FAILED;
        return makeNode1("B", makeNode0("0"));
    } else {//production2
        if (!match('1')) return FAILED;
        return makeNode1("B", makeNode0("1"));
    }
}

TREE ST() { //TODO
    if (!(lookahead('0') || lookahead('1'))) {//production epsilon
        return makeNode1("ST", makeNode0("e"));
    } else {//production1
        TREE s = S();
        if (s == NULL) return FAILED;
        return makeNode1("ST", s);
    }
}

TREE S() {//only one production
    TREE b = B();
    TREE st = ST();
    if (b == FAILED || st == FAILED) {
        return FAILED;
    } else {
        return makeNode2("S", b, st);
    }
}

TREE F() {
    if (lookahead('~')) { //production1
        if (!match('~')) return FAILED;
        TREE f = F();
        if (f == NULL) return FAILED;
        return makeNode2("F", makeNode0("~"), f);
    } else if (lookahead('(')) {//production2
        if (!match('(')) return FAILED;
        TREE e = E();
        if (e == NULL) return FAILED;
        if (!match(')')) return FAILED;
        return makeNode3("F", makeNode0("("), e, makeNode0(")"));
    } else {
        TREE s = S();
        if (s == NULL) return FAILED;
        return makeNode1("F", s);
    }
}

TREE TT() {
    if (!lookahead('&')) {//production epsilon
        return makeNode1("TT", makeNode0("e"));
    } else {//production1
        if (!match('&')) return FAILED;
        TREE t = T();
        if (t == NULL) return FAILED;
        return makeNode2("TT", makeNode0("&"), t);
    }
}


TREE T() {//only one production
    TREE f = F();
    TREE tt = TT();
    if (f == FAILED || tt == FAILED) {
        return FAILED;
    } else {
        return makeNode2("T", f, tt);
    }
}


TREE ET() {
    if (!lookahead('|')) { //production epsilon
        return makeNode1("ET", makeNode0("e"));
    } else { //production1
        if (!match('|')) return FAILED;
        TREE e = E();
        if (e == NULL) return FAILED;
        return makeNode2("ET", makeNode0("|"), e);
    }
}

TREE E() {//only one production
    TREE t = T();
    TREE et = ET();
    if (t == FAILED || et == FAILED) {
        return FAILED;
    } else {
        return makeNode2("E", t, et);
    }
}

