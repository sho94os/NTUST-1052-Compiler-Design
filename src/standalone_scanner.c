#include <stdio.h>
#define STANDALONE_SCANNER
#include "lex.yy.c"

int main(int argc, char **argv) {
    init_symbol_table();
    yylex();

    print_symbol_table();

    exit(0);
}
