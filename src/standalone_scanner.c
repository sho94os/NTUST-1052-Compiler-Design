#include <stdio.h>
#define STANDALONE_SCANNER
#include "lex.yy.c"

int main(int argc, char **argv) {
    init_symtab();
    yylex();

    print_symtab();

    exit(0);
}
