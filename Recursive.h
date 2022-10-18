#ifndef CSC173PROJECT2_TREE_H
#define CSC173PROJECT2_TREE_H
#include <stdbool.h>
typedef struct NODE *TREE;
struct NODE {
    char* label;
    TREE leftmostChild, rightSibling;
};

extern bool lookahead(char c);
extern bool match(char c);
extern TREE makeNode0(char* x);
extern TREE makeNode1(char* x, TREE t);
extern TREE makeNode2(char* x, TREE t1, TREE t2);
extern TREE makeNode3(char* x, TREE t1, TREE t2, TREE t3);
extern TREE makeNode4(char* x, TREE t1, TREE t2, TREE t3, TREE t4);
extern TREE parseStart();
extern void printTree(TREE tree1,int depth);
//extern void free_tree(TREE parseTree);
extern TREE E();
extern TREE ET();
extern TREE T();
extern TREE TT();
extern TREE F();
extern TREE S();
extern TREE ST();
extern TREE B();

//TREE parseTree; /* holds the result of the parse */
char *nextTerminal; /* current position in input string */

#endif //CSC173PROJECT2_TREE_H
