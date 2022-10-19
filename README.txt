CSC173 project2
Junfei Liu
jliu137@u.rochester.edu

I collaborate with Dingcheng Wang (dwang63@u.rochester.edu)

Our code can be compiled by
gcc -g -o run -std=c99 -Wall -Werror main.c Recursive.c Recursive.h stack.c stack.h table.c table.h

and you can run it by
./run.exe

Part one - recursive descent parsing -
It is called in main.c by Recursive_Descent_parser(). All methods and implementations are in Recursive.c
and Recursive.h. The implementation of tree data structure and lookahead() and match() functions are from
focs_11_27_gf.c.
There is nothing special to explain as all parsing methods are written just like the example in the
powerpoint slides.

Part two - table driven parsing -
It is called in main.c by Table_Driven_parser(). It implemented a stack data structure in stack.c(.h)
and includes important functions in table.c(.h). The parse() function in table.c is the function that
uses a table constructed by newTable() in table.c to do table-driven parsing. It is basically an
implementation of the universal parsing function on the powerpoint slides.

