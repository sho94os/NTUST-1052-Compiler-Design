#include <stdio.h>
#define STANDALONE_PARSER
#include "y.tab.c"

int main(int argc, char **argv) {
    init_symbol_table();
    yyparse();

    exit(0);
}
